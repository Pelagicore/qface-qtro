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


{{module|using_ns}}

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
    {{interface}}::registerQmlType(uri);
    {% endfor %}
}
