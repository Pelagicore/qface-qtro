{% set class = '{0}ServiceBase'.format(interface) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

{% set models = interface.properties|selectattr('is_model')|list %}
{% set primitive_models = interface.properties|selectattr('is_primitive_model')|list %}
{% set complex_models = interface.properties|selectattr('is_complex_model')|list %}

#include "{{interface|lower}}servicebase.h"
#include "engine/{{interface|lower}}engine.h"


{{class}}::{{class}}(QObject *parent)
    : {{interface}}SimpleSource(parent)
{% for property in interface.properties %}
{% if property.is_primitive_model %}
    , m_{{property}}(new VariantModel(this))
{% elif property.is_complex_model %}
    , m_{{property}}(new {{property.type.nested|upperfirst}}Model(this))
{% endif %}
{% endfor %}
    , m_engine(new {{interface}}Engine(this))
{
}

{{interface}}Engine* {{class}}::engine() const
{
    return m_engine;
}

{% for property in interface.properties if property.type.is_model %}
{% if property.type.nested.is_primitive %}
VariantModel* {{class}}::{{property}}() const
{
    return m_{{property}};
}
{% else %}
{{property.type.nested|upperfirst}}Model* {{class}}::{{property}}() const
{
    return m_{{property}};
}
{% endif %}
{% endfor %}

{% for operation in interface.operations %}
{{operation|returnType}} {{class}}::{{operation}}({{operation|parameters}})
{
    qDebug() << "{{class}}::{{operation}}(...): Not implemented";
    {% for parameter in operation.parameters %}
    Q_UNUSED({{parameter}})
    {% endfor %}
}
{% endfor %}

