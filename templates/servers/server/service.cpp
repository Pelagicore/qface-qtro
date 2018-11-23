{% set class = '{0}Service'.format(interface) %}

#include "{{class|lower}}.h"


{{class}}::{{class}}(QObject *parent)
    : Abstract{{interface}}Source(parent)
{% for property in interface.properties%}
{% if property.type.is_model and property.type.nested.is_primitive %}
    , m_{{property}}(new VariantModel(this))
{% elif property.type.is_model and property.type.nested.is_complex %}
    , m_{{property}}(new {{property.type.nested|upperfirst}}Model(this))
{% else %}
    , m_{{property}}({{property|qt.defaultValue}})
{% endif %}
{% endfor %}
{
}

{% for property in interface.properties %}
{% if property.type.is_model %}
QAbstractItemModel* {{class}}::{{property}}() const
{
    return m_{{property}};
}
{% else %}
{{property|qt.returnType}} {{class}}::{{property}}() const
{
    return m_{{property}};
}

void {{class}}::set{{property|upperfirst}}({{property|qt.signature}} {{property}})
{
    if (m_{{property}} != {{property}}) {
        m_{{property}} = {{property}};
        Q_EMIT {{property}}Changed({{property}});
    }
}
{% endif %}
{% endfor %}

{% for operation in interface.operations %}
{{operation|qt.returnType}} {{class}}::{{operation}}({{operation|qt.parameters}})
{
    qDebug() << "{{class}}::{{operation}}(...): Not implemented";
    {% for parameter in operation.parameters %}
    Q_UNUSED({{parameter}})
    {% endfor %}
}
{% endfor %}
