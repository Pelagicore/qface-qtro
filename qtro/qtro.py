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

from jinja2 import environmentfilter

here = Path(__file__).dirname()

logging.basicConfig()

log_config = Path('log.yaml')

if log_config.exists():
    logging.config.dictConfig(yaml.load(log_config.open('r')))
log = logging.getLogger(__name__)


class CustomFilters:

    @staticmethod
    def path(symbol):
        return symbol.qualified_name.replace('.', '/')

    @staticmethod
    def defaultValue(symbol):
        prefix = Filters.classPrefix
        t = symbol.type  # type: qface.domain.TypeSymbol
        if t.is_enum:
            value = next(iter(t.reference.members))
            return '{0}{1}Enum::{2}'.format(prefix, symbol.type, value)
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
        if symbol.type.is_enum:
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


def run(src, dst):
    log.debug('run {0} {1}'.format(src, dst))
    project = Path(dst).name
    classPrefix = ''
    system = FileSystem.parse(src)
    generator = Generator(search_path=here / 'templates')
    Filters.classPrefix = classPrefix
    generator.register_filter('defaultValue', CustomFilters.defaultValue)
    generator.register_filter('returnType', CustomFilters.returnType)
    generator.register_filter('parameterType', CustomFilters.parameterType)
    generator.register_filter('parameters', CustomFilters.parameters)
    generator.register_filter('signature', CustomFilters.signature)
    generator.register_filter('parse_doc', parse_doc)
    generator.register_filter('hash', qface.filters.hash)
    generator.register_filter('signalName', Filters.signalName)
    generator.register_filter('open_ns', Filters.open_ns)
    generator.register_filter('close_ns', Filters.close_ns)
    generator.register_filter('using_ns', Filters.using_ns)
    generator.register_filter('identifier', Filters.identifier)
    generator.register_filter('path', CustomFilters.path)

    ctx = {
        'dst': dst,
        'system': system,
        'classPrefix': classPrefix,
        'project': project,
    }

    ###############################################################
    # generate remotes
    ###############################################################

    dst = generator.apply('{{dst}}', ctx)
    generator.destination = dst

    generator.write('{{project}}.pro', 'project.pro', ctx)
    generator.write('lib{{project}}.pro', 'libproject.pro', ctx)
    generator.write('{{project}}.pri', 'project.pri', ctx)
    generator.write('CMakeLists.txt', 'CMakeLists.txt', ctx)

    generator.write('.qmake.conf', 'qmake.conf', ctx)
    generator.write('servers/servers.pro', 'servers/servers.pro', ctx)
    generator.write('plugins/plugins.pro', 'plugins/plugins.pro', ctx)
    generator.write('shared/server.conf', 'shared/server.conf', ctx)
    generator.write('shared/project.qrc', 'shared/project.qrc', ctx)

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
        dst = generator.apply('{{dst}}/plugins/{{module|identifier}}', ctx)
        generator.destination = dst

        # shared rep file per module
        generator.write('{{module|identifier}}.pro', 'plugins/plugin/plugin.pro', ctx)
        generator.write('{{module|identifier}}.pri', 'plugins/plugin/module.pri', ctx)
        generator.write('CMakeLists.txt', 'plugins/plugin/CMakeLists.txt', ctx)
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

        dst = generator.apply('{{dst}}/servers/{{module|identifier}}', ctx)
        generator.destination = dst

        generator.write('{{module|identifier}}.pro', 'servers/server/server.pro', ctx)
        generator.write('CMakeLists.txt', 'servers/server/CMakeLists.txt', ctx)
        generator.write('main.cpp', 'servers/server/main.cpp', ctx)
        generator.write('generated/generated.pri', 'servers/server/generated/generated.pri', ctx)
        generator.write('generated/variantmodel.h', 'servers/server/generated/variantmodel.h', ctx)
        generator.write('generated/variantmodel.cpp', 'servers/server/generated/variantmodel.cpp', ctx)
        # server side
        for interface in module.interfaces:
            ctx.update({'interface': interface})
            generator.write('{{interface|lower}}service.h', 'servers/server/service.h', ctx, preserve=True)
            generator.write('{{interface|lower}}service.cpp', 'servers/server/service.cpp', ctx, preserve=True)
            generator.write('generated/{{interface|lower}}servicebase.h', 'servers/server/generated/servicebase.h', ctx)
            generator.write('generated/{{interface|lower}}servicebase.cpp', 'servers/server/generated/servicebase.cpp', ctx)
        for struct in module.structs:
            log.debug('generate code for struct %s', struct)
            ctx.update({'struct': struct})
            generator.write('generated/{{struct|lower}}model.h', 'servers/server/generated/structmodel.h', ctx)
            generator.write('generated/{{struct|lower}}model.cpp', 'servers/server/generated/structmodel.cpp', ctx)

    # generate engine code
    for module in system.modules:
        log.debug('generate code for the engine modules')
        ctx.update({'module': module})
        dst = generator.apply('{{dst}}/servers/{{module|identifier}}/engine', ctx)
        generator.destination = dst
        generator.write('engine.pri', 'servers/server/engine/engine.pri', ctx)
        for interface in module.interfaces:
            ctx.update({'interface': interface})
            generator.write('{{interface|lower}}engine.h', 'servers/server/engine/engine.h', ctx, preserve=True)
            generator.write('{{interface|lower}}engine.cpp', 'servers/server/engine/engine.cpp', ctx, preserve=True)



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
