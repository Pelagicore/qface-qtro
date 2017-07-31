{% set class = '{0}ServiceBase'.format(interface) %}
{% set models = interface.properties|selectattr('is_model')|list %}
{% set primitive_models = interface.properties|selectattr('is_primitive_model')|list %}
{% set complex_models = interface.properties|selectattr('is_complex_model')|list %}
{% set properties = interface.properties|rejectattr('is_model')|list %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{interface|lower}}servicebase.h"
#include "engine/{{interface|lower}}engine.h"


{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
{% for property in models %}
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

{% for property in properties %}
{{property|returnType}} {{class}}::{{property}}() const
{
    return m_{{property}};
}

void {{class}}::set{{property|upperfirst}}({{property|parameterType}})
{
    if (m_{{property}} != {{property}}) {
        m_{{property}} = {{property}};
        Q_EMIT {{property}}Changed({{property}});
    }
}

void {{class}}::push{{property|upperfirst}}({{property|parameters}})
{
    set{{property|upperfirst}}({{property}});
}

{% endfor %}

{% for property in models %}
{{property|returnType}} {{class}}::{{property}}() const
{
    return m_{{property}};
}
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

