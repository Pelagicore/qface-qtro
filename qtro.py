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
    ctx = {'dst': dst, 'system': system, 'classPrefix': classPrefix}

    ###############################################################
    # generate remotes
    ###############################################################

    dst = generator.apply('{{dst}}/remotes', ctx)
    generator.destination = dst

    generator.write('remotes.pro', 'remotes.pro', ctx)
    generator.write('.qmake.conf', 'qmake.conf', ctx)
    generator.write('servers/servers.pro', 'server/servers.pro', ctx)
    generator.write('plugins/plugins.pro', 'plugins/plugins.pro', ctx)

    ###############################################################
    # generate plugins per module
    ###############################################################
    for module in system.modules:
        log.debug('generate code for module %s', module)

        ctx.update({'module': module})
        dst = generator.apply('{{dst}}/remotes/plugins/{{module|lower|replace(".", "-")}}', ctx)
        generator.destination = dst

        generator.write('{{module|lower|replace(".", "-")}}.pro', 'plugins/plugin.pro', ctx)
        generator.write('qmldir', 'plugins/qmldir', ctx)
        generator.write('plugin.cpp', 'plugins/plugin.cpp', ctx)
        generator.write('plugin.h', 'plugins/plugin.h', ctx)
        generator.write('generated/core.h', 'plugins/core.h', ctx)
        generator.write('generated/core.cpp', 'plugins/core.cpp', ctx)
        generator.write('generated/generated.pri', 'plugins/generated.pri', ctx)
        generator.write('generated/variantmodel.h', 'shared/variantmodel.h', ctx)
        generator.write('generated/variantmodel.cpp', 'shared/variantmodel.cpp', ctx)
        generator.write('docs/plugin.qdocconf', 'plugins/plugin.qdocconf', ctx)
        generator.write('docs/plugin-project.qdocconf', 'plugins/plugin-project.qdocconf', ctx)
        generator.write('docs/docs.pri', 'plugins/docs.pri', ctx)
        for interface in module.interfaces:
            log.debug('generate code for interface %s', interface)
            ctx.update({'interface': interface})
            generator.write('{{interface|lower}}.h', 'plugins/interface.h', ctx)
            generator.write('{{interface|lower}}.cpp', 'plugins/interface.cpp', ctx)
            generator.write('generated/abstract{{interface|lower}}.h', 'plugins/abstractinterface.h', ctx)
            generator.write('generated/abstract{{interface|lower}}.cpp', 'plugins/abstractinterface.cpp', ctx)
        for struct in module.structs:
            log.debug('generate code for struct %s', struct)
            ctx.update({'struct': struct})
            generator.write('generated/{{struct|lower}}.h', 'shared/struct.h', ctx)
            generator.write('generated/{{struct|lower}}.cpp', 'shared/struct.cpp', ctx)
            generator.write('generated/{{struct|lower}}model.h', 'shared/structmodel.h', ctx)
            generator.write('generated/{{struct|lower}}model.cpp', 'shared/structmodel.cpp', ctx)

        for enum in module.enums:
            log.debug('generate code for enum %s', enum)
            ctx.update({'enum': enum})
            generator.write('generated/{{enum|lower}}.h', 'shared/enum.h', ctx)

        # client side
        for interface in module.interfaces:
            log.debug('generate remote objects code')
            ctx.update({'interface': interface})
            generator.write('generated/{{interface|lower}}replica.h', 'qtro/replica.h', ctx)

    ###############################################################
    # generate server per module
    ###############################################################
    for module in system.modules:
        log.debug('generate code for server module %s', module)
        ctx.update({'module': module})

        dst = generator.apply('{{dst}}/remotes/servers/{{module|lower|replace(".", "-")}}', ctx)
        generator.destination = dst

        generator.write('{{module|lower|replace(".", "-")}}.pro', 'server/server.pro', ctx)
        generator.write('main.cpp', 'server/main.cpp', ctx)
        generator.write('generated/generated.pri', 'server/generated.pri', ctx)
        generator.write('generated/variantmodel.h', 'shared/variantmodel.h', ctx)
        generator.write('generated/variantmodel.cpp', 'shared/variantmodel.cpp', ctx)
        # server side
        for interface in module.interfaces:
            ctx.update({'interface': interface})
            generator.write('generated/{{interface|lower}}sourceapi.h', 'server/sourceapi.h', ctx)
            generator.write('generated/{{interface|lower}}abstractsource.h', 'server/abstractsource.h', ctx)
            generator.write('generated/{{interface|lower}}abstractsource.cpp', 'server/abstractsource.cpp', ctx)
            generator.write('{{interface|lower}}service.h', 'server/service.h', ctx, preserve=True)
            generator.write('{{interface|lower}}service.cpp', 'server/service.cpp', ctx, preserve=True)
        for struct in module.structs:
            log.debug('generate code for struct %s', struct)
            ctx.update({'struct': struct})
            generator.write('generated/{{struct|lower}}.h', 'shared/struct.h', ctx)
            generator.write('generated/{{struct|lower}}.cpp', 'shared/struct.cpp', ctx)
            generator.write('generated/{{struct|lower}}model.h', 'shared/structmodel.h', ctx)
            generator.write('generated/{{struct|lower}}model.cpp', 'shared/structmodel.cpp', ctx)
        for enum in module.enums:
            log.debug('generate code for enum %s', enum)
            ctx.update({'enum': enum})
            generator.write('generated/{{enum|lower}}.h', 'shared/enum.h', ctx)


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
