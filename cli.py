#!/usr/bin/env python3
# Copyright (c) Pelagicore AB 2016

import click
from subprocess import call
from watchdog.events import FileSystemEventHandler
from watchdog.observers import Observer
from path import Path
import time
import os
import yaml
import logging
import logging.config
from livereload import Server, shell


here = os.path.dirname(__file__)

logging.basicConfig()
with open('log.yaml', 'r') as fp:
    logging.config.dictConfig(yaml.load(fp))
log = logging.getLogger(__name__)


def sh(cmd, all=False, **kwargs):
    click.echo('$ {0}'.format(cmd))
    return call(cmd, shell=True, **kwargs)


@click.group()
def cli():
    pass


@cli.command()
@click.option('--debug/--nodebug')
def test(debug):
    """run the tests"""
    sh('python3 -m pytest -v -s -l {0}'.format('-pdb' if debug else ''))


@cli.command()
def test_ci():
    """run the tests for CI integration"""
    sh('python3 -m pytest --cov=qface -v -l tests/')


class RunTestChangeHandler(FileSystemEventHandler):
    def __init__(self, clickContext):
        super().__init__()
        self.clickContext = clickContext

    def on_any_event(self, event):
        if event.is_directory:
            return
        if Path(event.src_path).ext == '.py':
            sh('python3 -m pytest')


@cli.command()
@click.pass_context
def test_monitor(ctx):
    """run the tests and re-run on changes"""
    sh('python3 -m pytest')
    while True:
        event_handler = RunTestChangeHandler(ctx)
        observer = Observer()
        observer.schedule(event_handler, './tests', recursive=True)
        observer.schedule(event_handler, './qface', recursive=True)
        observer.start()
        try:
            while True:
                time.sleep(1)
        except KeyboardInterrupt:
            observer.stop()
        observer.join()


@click.option('--editable/--no-editable', default=False, help='install editable package')
@cli.command()
def install(editable):
    """install the script onto the system using pip3"""
    script_dir = str(Path(__file__).parent.abspath())
    click.secho(script_dir, fg='blue')
    if editable:
        sh('pip3 install --editable {0} --upgrade'.format(script_dir))
    else:
        sh('pip3 install {0} --upgrade'.format(script_dir))


@cli.command()
def uninstall():
    """uninstall the script from the system using pip3"""
    sh('pip3 uninstall qface')


@cli.command()
def upload():
    sh('twine upload dist/*')
    Path('build').rmtree_p()

@cli.command()
def pack():
    Path('build').rmtree_p()
    dist = Path('dist')
    dist.rmtree_p()
    dist.makedirs_p()
    sh('python3 setup.py bdist_wheel')
    sh('unzip -l dist/*.whl')


@cli.command()
def docs_serve():
    server = Server()
    server.watch('docs/*.rst', shell('make html', cwd='docs'))
    server.serve(root='docs/_build/html', open_url=True)


if __name__ == '__main__':
    cli()
