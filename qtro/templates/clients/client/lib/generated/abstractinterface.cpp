{% set class = 'Abstract{0}'.format(interface) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"

#include <QtQml>
#include "core.h"

{{interface|using_ns}}

/*!
   \qmltype {{interface}}
   \inqmlmodule {{module}}
{% with doc = interface.comment|parse_doc %}
   \brief {{doc.brief}}

   {{doc.description}}
{% endwith %}
*/
{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
{
    QRemoteObjectNode* node = Core::instance()->node();

    m_replica.reset(node->acquire<{{interface}}Replica>("{{interface.qualified_name}}"));

    if(!m_replica) {
      qFatal("Unable to acquire {{interface}}Replica");
    }
{% for property in interface.properties if property.type.is_model %}
    m_{{property|lowerfirst}}.reset(node->acquireModel("{{property.qualified_name}}"));
    if(!m_{{property|lowerfirst}}) {
      qFatal("Unable to acquire {{property.qualified_name}}");
    }
{% endfor %}

    setupConnections();
}


{{class}}::~{{class}}()
{
}

{% for property in interface.properties if not property.type.is_model %}
/*!
   \qmlproperty {{property.type}} {{interface}}::{{property}}
{% with doc = property.comment|parse_doc %}
   \brief {{doc.brief}}

   {{doc.description}}
{% endwith %}
*/

void {{class}}::set{{property|upperfirst}}({{ property|parameterType }})
{
    m_replica->push{{property|upperfirst}}({{property}});
}

{{property|returnType}} {{class}}::{{property}}() const
{
    return m_replica->{{property}}();
}
{% endfor %}
{% for property in interface.properties if property.type.is_model %}
QAbstractItemModelReplica* {{class}}::{{property}}() const
{
    return m_{{property}}.data();
}

{% endfor %}

{%- for operation in interface.operations %}
/*!
   \qmlmethod {{operation.type}} {{interface}}::{{operation}}({{operation.parameters|map('parameterType')|join(', ')}})
{% with doc = operation.comment|parse_doc %}
   \brief {{doc.brief}}
   {{doc.description}}
{% endwith %}
*/
{{operation|returnType}} {{class}}::{{operation}}({{operation.parameters|map('parameterType')|join(', ')}})
{
    m_replica->{{operation}}({{operation.parameters|join(',')}});
}
{% endfor %}

void {{class}}::setupConnections()
{
  {% for property in interface.properties if not property.type.is_model %}
  connect(m_replica.data(), &{{interface}}Replica::{{property}}Changed, this, &{{class}}::{{property}}Changed);
  {% endfor %}
  {% for signal in interface.signals %}
  connect(m_replica.data(), &{{interface}}Replica::{{signal}}, this, &{{class}}::{{signal}});
  {% endfor %}
}


