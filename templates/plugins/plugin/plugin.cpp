{# Copyright (c) Pelagicore AB 2016 #}
{% set module_name = 'Qml{0}Module'.format(module.module_name) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "plugin.h"

#include <QtQml>

{% for interface in module.interfaces %}
#include "{{interface|lower}}.h"
{% endfor %}

Plugin::Plugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{
}

void Plugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine)
    Q_UNUSED(uri)
}

void Plugin::registerTypes(const char *uri)
{
{% for interface in module.interfaces %}
    {{interface}}::registerQmlTypes(uri, 1, 0);
{% endfor %}
{% for struct in module.structs %}
    // {{struct}}::registerTypes();
{% endfor %}
{% for enum in module.enums %}
    // {{enum}}::registerTypes();
{% endfor %}
}
