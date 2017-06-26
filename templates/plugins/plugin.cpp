{# Copyright (c) Pelagicore AB 2016 #}
{% set module_name = 'Qml{0}Module'.format(module.module_name) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "plugin.h"

#include <QtQml>
#include <QtRemoteObjects>

#include "generated/{{module_name|lower}}.h"

{% for interface in module.interfaces %}
#include "qml{{interface|lower}}.h"
{% endfor %}


Plugin* Plugin::s_instance(nullptr);

Plugin::Plugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
    , m_node(new QRemoteObjectNode(this))
{
    if (s_instance) {
        qFatal("You can not instantiate the plugin twice");
    }
    s_instance = this;
    m_node->setRegistryUrl(QUrl(QStringLiteral("local:{{module}}")));
}

void Plugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine)
    Q_UNUSED(uri)
}

void Plugin::registerTypes(const char *uri)
{
    {{module_name}}::registerTypes();
    // @uri {{module|lower}}
    {{module_name}}::registerQmlTypes(uri, 1, 0);
{% for interface in module.interfaces %}
    Qml{{interface}}::registerQmlTypes(uri, 1, 0);
{% endfor %}
}

Plugin* Plugin::instance()
{
    if(!s_instance) {
        qFatal("No instance found");
    }
    return s_instance;
}
