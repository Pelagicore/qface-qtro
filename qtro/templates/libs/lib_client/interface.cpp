{% set class = '{0}'.format(interface) %}
{% set models = interface.properties|selectattr('is_model')|list %}
{% set primitive_models = interface.properties|selectattr('is_primitive_model')|list %}
{% set complex_models = interface.properties|selectattr('is_complex_model')|list %}
{% set properties = interface.properties|rejectattr('is_model')|list %}
{% set cat = 'lib_client_{0}'.format(module|identifier) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"

#include <QtQml>

{{interface|using_ns}}


QObject* {{class|lower}}_singletontype_provider(QQmlEngine*, QJSEngine*)
{
      return new {{class}}();
}


/*!
   \qmltype {{interface}}
   \inqmlmodule {{module}}
{% with doc = interface.comment|parse_doc %}
   \brief {{doc.description|join()}}
{% endwith %}
*/
{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
{% for property in primitive_models %}
    , m_{{property}}({{property|defaultValue}})
{% endfor %}
{% for property in complex_models %}
    , m_{{property}}({{property|defaultValue}})
{% endfor %}

{
    qCDebug({{cat}}) << "{{class}}::{{class}}()";
    QRemoteObjectNode* node = Core::instance()->node();

    m_replica.reset(node->acquire<{{interface}}Replica>("{{interface.qualified_name}}"));

    if(!m_replica) {
      qFatal("Unable to acquire {{interface}}Replica");
    }
{% for property in models %}
    m_{{property|lowerfirst}}Model.reset(node->acquireModel("{{property.qualified_name}}"));
    if(!m_{{property|lowerfirst}}Model) {
      qFatal("Unable to acquire {{property.qualified_name}}");
    }
    m_{{property|lowerfirst}}->setSourceModel(m_{{property|lowerfirst}}Model.data());

{% endfor %}

    setupConnections();
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


{% for property in properties %}
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
{% for property in primitive_models %}
{{property|returnType}}{{class}}::{{property}}() const
{
    return m_{{property}};
}
{% endfor %}
{% for property in complex_models %}
{{property|returnType}}{{class}}::{{property}}() const
{
    return m_{{property}};
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
    return m_replica->{{operation}}({{operation.parameters|join(',')}});
}
{% endfor %}

void {{class}}::setupConnections()
{
  qCDebug({{cat}}) << "{{class}}::setupConnections()";
  {% for property in interface.properties if not property.type.is_model %}
  connect(m_replica.data(), &{{interface}}Replica::{{property}}Changed, this, &{{class}}::{{property}}Changed);
  {% endfor %}
  {% for signal in interface.signals %}
  connect(m_replica.data(), &{{interface}}Replica::{{signal}}, this, &{{class}}::{{signal}});
  {% endfor %}
}


