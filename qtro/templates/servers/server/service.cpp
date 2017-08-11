{% set class = '{0}Service'.format(interface) %}
{% set models = interface.properties|selectattr('is_model')|list %}
{% set primitive_models = interface.properties|selectattr('is_primitive_model')|list %}
{% set complex_models = interface.properties|selectattr('is_complex_model')|list %}
{% set properties = interface.properties|rejectattr('is_model')|list %}
{% set cat = 'lib_service_{0}'.format(module|identifier) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"



{{module|open_ns}}

class {{class}}Private
{
public:
    {{class}}Private({{class}} *q)
        : q_ptr(q)
{% if 'scaffold' in features %}
{% for property in properties %}
        , {{property}}({{property|defaultValue}})
{% endfor %}
{% for property in models %}
{% if property.is_primitive_model %}
        , {{property}}(new VariantModel(q))
{% elif property.is_complex_model %}
        , {{property}}(new {{property.type.nested|upperfirst}}Model(q))
{% endif %}
{% endfor %}
{% endif %}
    {}

public: // data
    {{class}} *q_ptr;
{% if 'scaffold' in features %}
{% for property in properties %}
    {{property|returnType}} {{property}};
{% endfor %}
{% for property in models %}
    {{property|returnType}} {{property}};
{% endfor %}
{% endif %}
};

{{module|close_ns}}

{{module|using_ns}}

{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
    , d_ptr(new {{class}}Private(this))
{
    qCDebug({{cat}}) << "{{class}}::{{class}}()";
}

{{class}}::~{{class}}()
{
}

{% for property in properties %}
{{property|returnType}} {{class}}::{{property}}() const
{
{% if 'scaffold' in features %}
    return d_ptr->{{property}};
{% else %}
    // TODO: implement {{class}}::{{property}}
    return {{property|defaultValue}};
{% endif %}
}

void {{class}}::set{{property|upperfirst}}({{property|parameterType}})
{
{% if 'scaffold' in features %}
    if (d_ptr->{{property}} != {{property}}) {
        d_ptr->{{property}} = {{property}};
        Q_EMIT {{property}}Changed({{property}});
    }
{% else %}
    // TODO: implement {{class}}::set{{property|upperfirst}}(..)
{% endif %}
}

void {{class}}::push{{property|upperfirst}}({{property|parameters}})
{
{% if 'scaffold' in features %}
    set{{property|upperfirst}}({{property}});
{% else %}
    // TODO: implement {{class}}::push{{property|upperfirst}}(..)
{% endif %}
}
{% endfor %}

{% for property in models %}
QAbstractItemModel *{{class}}::{{property}}() const
{
{% if 'scaffold' in features %}
    return d_ptr->{{property}};
{% else %}
    // TODO: implement {{class}}::{{property}}()
    return nullptr;
{% endif %}
}
{% endfor %}
{% for operation in interface.operations %}
{{operation|returnType}} {{class}}::{{operation}}({{operation|parameters}})
{
{% if 'scaffold' in features %}
    qCDebug({{cat}}) << "{{class}}::{{operation}}(...): Not implemented";
    {% for parameter in operation.parameters %}
    Q_UNUSED({{parameter}})
    {% endfor %}
    return {{operation|defaultValue}};
{% else %}
    return {{operation|defaultValue}};
{% endif %}
}

{% endfor %}

