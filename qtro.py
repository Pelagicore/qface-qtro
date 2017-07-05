#!/usr/bin/env python3
# Copyright (c) Pelagicore AB 2016

import click
import logging
import logging.config
import yaml
from path import Path

from qface.generator import FileSystem, Generator
from qface.helper.qtcpp import Filters
from qface.helper.doc import parse_doc
from qface.watch import monitor
from qface.shell import sh
import qface.filters


here = Path(__file__).dirname()

logging.config.dictConfig(yaml.load(open(here / 'log.yaml')))

log = logging.getLogger(__file__)


def run(src, dst):
    log.debug('run {0} {1}'.format(src, dst))
    project = Path(dst).name
    classPrefix = ''
    system = FileSystem.parse(src)
    generator = Generator(search_path=here / 'templates')
    Filters.classPrefix = classPrefix
    generator.register_filter('returnType', Filters.returnType)
    generator.register_filter('parameterType', Filters.parameterType)
    generator.register_filter('defaultValue', Filters.defaultValue)
    generator.register_filter('parse_doc', parse_doc)
    generator.register_filter('hash', qface.filters.hash)
    generator.register_filter('signalName', Filters.signalName)
    generator.register_filter('parameters', Filters.parameters)
    generator.register_filter('signature', Filters.signature)

    ctx = {
        'dst': dst,
        'system': system,
        'classPrefix': classPrefix,
        'project': project
    }

    ###############################################################
    # generate remotes
    ###############################################################

    dst = generator.apply('{{dst}}', ctx)
    generator.destination = dst

    generator.write('{{project}}.pro', 'project.pro', ctx)
    generator.write('.qmake.conf', 'qmake.conf', ctx)
    generator.write('servers/servers.pro', 'servers/servers.pro', ctx)
    generator.write('plugins/plugins.pro', 'plugins/plugins.pro', ctx)

    ###############################################################
    # generate shared code per module
    ###############################################################
    for module in system.modules:
        ctx.update({'module': module})
        generator.write('shared/{{module}}.rep', 'shared/repc.rep', ctx)

    ###############################################################
    # generate plugins per module
    ###############################################################
    for module in system.modules:
        log.debug('generate code for module %s', module)

        ctx.update({'module': module})
        dst = generator.apply('{{dst}}/plugins/{{module|lower|replace(".", "-")}}', ctx)
        generator.destination = dst

        generator.write('{{module|lower|replace(".", "-")}}.pro', 'plugins/plugin/plugin.pro', ctx)
        generator.write('qmldir', 'plugins/plugin/qmldir', ctx)
        generator.write('plugin.cpp', 'plugins/plugin/plugin.cpp', ctx)
        generator.write('plugin.h', 'plugins/plugin/plugin.h', ctx)
        generator.write('docs/plugin.qdocconf', 'plugins/plugin/plugin.qdocconf', ctx)
        generator.write('docs/plugin-project.qdocconf', 'plugins/plugin/plugin-project.qdocconf', ctx)
        generator.write('docs/docs.pri', 'plugins/plugin/docs.pri', ctx)
        generator.write('generated/generated.pri', 'plugins/plugin/generated/generated.pri', ctx)
        generator.write('generated/core.h', 'plugins/plugin/generated/core.h', ctx)
        generator.write('generated/core.cpp', 'plugins/plugin/generated/core.cpp', ctx)
        for interface in module.interfaces:
            log.debug('generate code for interface %s', interface)
            ctx.update({'interface': interface})
            generator.write('{{interface|lower}}.h', 'plugins/plugin/interface.h', ctx)
            generator.write('{{interface|lower}}.cpp', 'plugins/plugin/interface.cpp', ctx)
            generator.write('generated/abstract{{interface|lower}}.h', 'plugins/plugin/generated/abstractinterface.h', ctx)
            generator.write('generated/abstract{{interface|lower}}.cpp', 'plugins/plugin/generated/abstractinterface.cpp', ctx)

    ###############################################################
    # generate server per module
    ###############################################################
    for module in system.modules:
        log.debug('generate code for server module %s', module)
        ctx.update({'module': module})

        dst = generator.apply('{{dst}}/servers/{{module|lower|replace(".", "-")}}', ctx)
        generator.destination = dst

        generator.write('{{module|lower|replace(".", "-")}}.pro', 'servers/server/server.pro', ctx)
        generator.write('main.cpp', 'servers/server/main.cpp', ctx)
        generator.write('generated/generated.pri', 'servers/server/generated/generated.pri', ctx)
        generator.write('generated/variantmodel.h', 'servers/server/generated/variantmodel.h', ctx)
        generator.write('generated/variantmodel.cpp', 'servers/server/generated/variantmodel.cpp', ctx)
        # server side
        for interface in module.interfaces:
            ctx.update({'interface': interface})
            generator.write('{{interface|lower}}service.h', 'servers/server/service.h', ctx, preserve=True)
            generator.write('{{interface|lower}}service.cpp', 'servers/server/service.cpp', ctx, preserve=True)
            generator.write('generated/{{interface|lower}}abstractsource.h', 'servers/server/generated/abstractsource.h', ctx)
            generator.write('generated/{{interface|lower}}abstractsource.cpp', 'servers/server/generated/abstractsource.cpp', ctx)
        for struct in module.structs:
            log.debug('generate code for struct %s', struct)
            ctx.update({'struct': struct})
            generator.write('generated/{{struct|lower}}model.h', 'servers/server/generated/structmodel.h', ctx)
            generator.write('generated/{{struct|lower}}model.cpp', 'servers/server/generated/structmodel.cpp', ctx)


@click.command()
@click.option('--reload/--no-reload', default=False)
@click.option('cmd', '--exec', type=click.Path(exists=True), multiple=True)
@click.argument('src', nargs=-1, type=click.Path(exists=True))
@click.argument('dst', nargs=1, type=click.Path(exists=True))
def app(src, dst, reload, cmd):
    """Takes several files or directories as src and generates the code
    in the given dst directory."""
    if reload:
        script = Path(__file__).abspath()
        monitor(script, src, dst)
    else:
        run(src, dst)
        sh(cmd)


if __name__ == '__main__':
    app()
