#!/usr/bin/env python3
# Copyright (c) Pelagicore AB 2016

import click
import logging
import logging.config
import yaml
from path import Path

from qface.generator import FileSystem, RuleGenerator
from qface.helper.qtcpp import Filters
from qface.helper.doc import parse_doc
from qface.watch import monitor
from qface.shell import sh
import qface.filters

from jinja2 import environmentfilter

here = Path(__file__).dirname()

logging.basicConfig()

log_config = Path('log.yaml')

if log_config.exists():
    logging.config.dictConfig(yaml.load(log_config.open('r')))
log = logging.getLogger(__name__)


features = set()


class CustomFilters:

    @staticmethod
    def path(symbol):
        return symbol.qualified_name.replace('.', '/')

    @staticmethod
    def defaultValue(symbol):
        prefix = Filters.classPrefix
        if symbol.kind == 'enum':
            value = next(iter(symbol.members))
            return '{0}{1}Enum::{1}::{2}'.format(prefix, symbol, value)
        t = symbol.type  # type: qface.domain.TypeSymbol
        if t.is_enum:
            value = next(iter(t.reference.members))
            return '{0}{1}Enum::{1}::{2}'.format(prefix, t, value)
        return Filters.defaultValue(symbol)

    @staticmethod
    def parameterType(symbol):
        prefix = Filters.classPrefix
        if symbol.type.is_enum:
            return '{0}{1}Enum::{1} {2}'.format(prefix, symbol.type, symbol)
        return Filters.parameterType(symbol)

    @staticmethod
    def returnType(symbol):
        prefix = Filters.classPrefix
        if symbol.kind == 'enum':
            return '{0}{1}Enum::{1}'.format(prefix, symbol)
        elif symbol.type.is_enum:
            return '{0}{1}Enum::{1}'.format(prefix, symbol.type)
        return Filters.returnType(symbol)

    @staticmethod
    @environmentfilter
    def parameters(env, s, filter=None, spaces=True):
        if not filter:
            filter = CustomFilters.parameterType
        return Filters.parameters(env, s, filter, spaces)

    @staticmethod
    @environmentfilter
    def signature(env, s, expand=False, filter=None):
        if not filter:
            filter = CustomFilters.returnType
        return Filters.signature(env, s, expand, filter)

    @staticmethod
    def filters():
        return {

        }


def run(src, dst):
    log.debug('run {0} {1}'.format(src, dst))
    project = Path(dst).name
    classPrefix = ''
    system = FileSystem.parse(src)

    context = {
        'dst': dst,
        'system': system,
        'classPrefix': classPrefix,
        'project': project,
        'features': features,
    }

    generator = RuleGenerator(search_path=here / 'templates', destination=dst, context=context, features=features)

    Filters.classPrefix = classPrefix
    generator.filters.update({
        'defaultValue': CustomFilters.defaultValue,
        'returnType': CustomFilters.returnType,
        'parameterType': CustomFilters.parameterType,
        'parameters': CustomFilters.parameters,
        'signature': CustomFilters.signature,
        'parse_doc': parse_doc,
        'hash': qface.filters.hash,
        'jsonify': qface.filters.jsonify,
        'signalName': Filters.signalName,
        'open_ns': Filters.open_ns,
        'close_ns': Filters.close_ns,
        'using_ns': Filters.using_ns,
        'ns': Filters.ns,
        'identifier': Filters.identifier,
        'path': CustomFilters.path,
    })

    generator.process_rules(here / 'qtro.yml', system)


@click.command()
@click.option('--reload/--no-reload', default=False, help="Auto reload script on changes")
@click.option('--scaffold/--no-scaffold', default=True, help="Generates scaffolding app")
@click.option('--apps/--no-apps', default=True, help="Generates apps stubs")
@click.option('--servers/--no-servers', default=True, help="Generates server code")
@click.option('cmd', '--exec', type=click.Path(exists=True), multiple=True, help="Executes script after code generation")
@click.argument('src', nargs=-1, type=click.Path(exists=True))
@click.argument('dst', nargs=1, type=click.Path(exists=True))
def app(src, dst, reload, cmd, scaffold, apps, servers):
    """Takes several files or directories as src and generates the code
    in the given dst directory."""
    global features
    if scaffold:
        features.add('scaffold')
    if apps:
        features.add('apps')
    if servers:
        features.add('servers')
    if reload:
        argv = sys.argv.copy()
        argv.remove('--reload')
        monitor(here, src, dst, argv)
    else:
        run(src, dst)
        sh(cmd)


if __name__ == '__main__':
    app()
