{% set class = '{0}'.format(interface) %}
{% set cat = 'lib_client_{0}'.format(module|identifier) %}
/****************************************************************************
** This is a preserved file.
** Changes will not be overriden by the generator.
** To reset the file you need to delete it first.
****************************************************************************/

#include "{{class|lower}}.h"

#include <QtQml>
#include "core.h"


{{interface|using_ns}}
/*!
    \inqmlmodule {{module}} 1.0
 */

QObject* {{class|lower}}_singletontype_provider(QQmlEngine*, QJSEngine*)
{
      return new {{class}}();
}


/*!
   \qmltype {{interface}}
   \inqmlmodule {{module}}
{% with doc = interface.comment|parse_doc %}
   \brief {{doc.brief}}

   {{doc.description}}
{% endwith %}
*/

{{interface.comment}}
{{class}}::{{class}}(QObject *parent)
    : {{interface}}Base(parent)
{
    qCDebug({{cat}}) << "{{class}}::{{class}}()";
}

{{class}}::~{{class}}()
{
}

void {{class}}::registerQmlType(const char* uri, int majorVersion, int minorVersion)
{
    qCDebug({{cat}}) << "{{class}}::registerQmlType()";
    Core::registerTypes(uri);
    {% if 'singleton' in interface.tags %}
    qmlRegisterSingletonType<{{class}}>(uri, majorVersion, minorVersion, "{{interface}}", {{class|lower}}_singletontype_provider);
    {% else %}
    qmlRegisterType<{{class}}>(uri, majorVersion, minorVersion, "{{interface}}");
    {% endif %}
}
