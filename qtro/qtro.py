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

    generator = RuleGenerator(search_path=here/'templates', destination=dst, context=context, features=features)
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

    generator.process_rules(here/'qtro.yml', system)


    ###############################################################
    # generate remotes
    ###############################################################

    # generator.destination = '{{dst}}'

    # generator.write('{{project}}.pro', 'project.pro')
    # generator.write('lib{{project}}.pro', 'libproject.pro')
    # generator.write('{{project}}.pri', 'project.pri')
    # generator.write('CMakeLists.txt', 'CMakeLists.txt')

    # generator.write('.qmake.conf', 'qmake.conf')
    # generator.write('servers/servers.pro', 'servers/servers.pro')
    # generator.write('clients/clients.pro', 'clients/clients.pro')
    # generator.write('apps/apps.pro', 'apps/apps.pro', preserve=True)
    # generator.write('shared/server.conf', 'shared/server.conf')
    # generator.write('shared/project.qrc', 'shared/project.qrc')

    # ###############################################################
    # # generate shared code per module
    # ###############################################################
    # for module in system.modules:
    #     generator.context.update({'module': module})
    #     generator.write('shared/{{module}}.rep', 'shared/repc.rep')

    # ###############################################################
    # # generate plugins per module
    # ###############################################################
    # for module in system.modules:
    #     log.debug('generate code for module %s', module)
    #     generator.context.update({'module': module})
    #     generator.destination = '{{dst}}/clients/{{module|identifier}}'

    #     # shared rep file per module
    #     generator.write('{{module|identifier}}.pro', 'clients/client/client.pro')
    #     generator.write('plugin/{{module|identifier}}.pro', 'clients/client/plugin/plugin.pro')
    #     generator.write('lib/lib.pro', 'clients/client/lib/lib.pro')
    #     generator.write('lib/lib.pri', 'clients/client/lib/lib.pri')
    #     generator.write('lib/uselib.pri', 'clients/client/lib/uselib.pri')
    #     generator.write('CMakeLists.txt', 'clients/client/CMakeLists.txt')
    #     generator.write('plugin/plugin.pro', 'clients/client/plugin/plugin.pro')
    #     generator.write('plugin/qmldir', 'clients/client/plugin/qmldir')
    #     generator.write('plugin/plugin.cpp', 'clients/client/plugin/plugin.cpp')
    #     generator.write('plugin/plugin.h', 'clients/client/plugin/plugin.h')
    #     generator.write('docs/client.qdocconf', 'clients/client/docs/online.qdocconf')
    #     generator.write('docs/client-project.qdocconf', 'clients/client/docs/project.qdocconf')
    #     generator.write('docs/docs.pri', 'clients/client/docs/docs.pri')
    #     generator.write('lib/generated/generated.pri', 'clients/client/lib/generated/generated.pri')
    #     generator.write('lib/generated/core.h', 'clients/client/lib/generated/core.h')
    #     generator.write('lib/generated/core.cpp', 'clients/client/lib/generated/core.cpp')
    #     for interface in module.interfaces:
    #         log.debug('generate code for interface %s', interface)
    #         generator.context.update({'interface': interface})
    #         generator.write('lib/{{interface|lower}}.h', 'clients/client/lib/interface.h')
    #         generator.write('lib/{{interface|lower}}.cpp', 'clients/client/lib/interface.cpp')
    #         generator.write('lib/generated/abstract{{interface|lower}}.h', 'clients/client/lib/generated/abstractinterface.h')
    #         generator.write('lib/generated/abstract{{interface|lower}}.cpp', 'clients/client/lib/generated/abstractinterface.cpp')

    # ###############################################################
    # # generate server per module
    # ###############################################################
    # for module in system.modules:
    #     log.debug('generate code for server module %s', module)
    #     generator.context.update({'module': module})

    #     generator.destination = '{{dst}}/servers/{{module|identifier}}'

    #     generator.write('{{module|identifier}}.json', 'servers/server/meta.json')
    #     generator.write('{{module|identifier}}.pro', 'servers/server/server.pro')
    #     generator.write('CMakeLists.txt', 'servers/server/CMakeLists.txt')
    #     generator.write('main.cpp', 'servers/server/main.cpp')
    #     generator.write('generated/generated.pri', 'servers/server/generated/generated.pri')
    #     generator.write('generated/variantmodel.h', 'servers/server/generated/variantmodel.h')
    #     generator.write('generated/variantmodel.cpp', 'servers/server/generated/variantmodel.cpp')
    #     # server side
    #     for interface in module.interfaces:
    #         generator.context.update({'interface': interface})
    #         generator.write('{{interface|lower}}service.h', 'servers/server/service.h', preserve=True)
    #         generator.write('{{interface|lower}}service.cpp', 'servers/server/service.cpp', preserve=True)
    #         generator.write('generated/{{interface|lower}}servicebase.h', 'servers/server/generated/servicebase.h')
    #         generator.write('generated/{{interface|lower}}servicebase.cpp', 'servers/server/generated/servicebase.cpp')
    #     for struct in module.structs:
    #         log.debug('generate code for struct %s', struct)
    #         generator.context.update({'struct': struct})
    #         generator.write('generated/{{struct|lower}}model.h', 'servers/server/generated/structmodel.h')
    #         generator.write('generated/{{struct|lower}}model.cpp', 'servers/server/generated/structmodel.cpp')

    # # generate engine code
    # for module in system.modules:
    #     log.debug('generate code for the engine modules')
    #     generator.context.update({'module': module})
    #     generator.destination = '{{dst}}/servers/{{module|identifier}}/engine'
    #     generator.write('engine.pri', 'servers/server/engine/engine.pri')
    #     for interface in module.interfaces:
    #         generator.context.update({'interface': interface})
    #         generator.write('{{interface|lower}}engine.h', 'servers/server/engine/engine.h', preserve=True)
    #         generator.write('{{interface|lower}}engine.cpp', 'servers/server/engine/engine.cpp', preserve=True)

    # if Features.scaffold:
    #     generator.destination = '{{dst}}/apps/{{project|lower}}app'
    #     generator.write('{{project|lower}}app.pro', 'apps/app/app.pro')
    #     generator.write('qml.qrc', 'apps/app/qml.qrc')
    #     generator.write('main.cpp', 'apps/app/main.cpp')
    #     generator.write('qml/Main.qml', 'apps/app/qml/Main.qml')
    #     generator.write('qtquickcontrols2.conf', 'apps/app/qtquickcontrols2.conf')


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
        script = Path(__file__).abspath()
        monitor(script, src, dst)
    else:
        run(src, dst)
        sh(cmd)


if __name__ == '__main__':
    app()
