{% set class = '{0}AbstractSource'.format(interface) %}

#include "{{interface|lower}}abstractsource.h"


{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
{% for property in interface.properties if property.type.is_model and property.type.nested.is_complex %}
    , m_{{property|lowerfirst}}(new Qml{{property.type.nested}}Model(this))
{% endfor %}
{% for property in interface.properties if property.type.is_model and property.type.nested.is_primitive %}
    , m_{{property|lowerfirst}}(new QmlVariantModel(this))
{% endfor %}
{
}

{{class}}::~{{class}}()
{
}

{% for property in interface.properties %}
{{property|returnType}} {{class}}::{{property}}() const
{
    {% if property.type.is_model %}
    return m_{{property}};
    {% else %}
    return {{property|defaultValue}};
    {% endif %}
}
{% endfor %}
{% for property in interface.properties %}
void {{class}}::set{{property|upperfirst}}({{property|parameterType}})
{
    Q_UNUSED({{property}})
}
{% endfor %}
{% for operation in interface.operations %}
{{operation|returnType}} {{class}}::{{operation}}({{operation|parameters}})
{
    {% for parameter in operation.parameters %}
    Q_UNUSED({{parameter}})
    {% endfor %}
}
{% endfor %}

