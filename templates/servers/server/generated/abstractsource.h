{% set class = '{0}AbstractSource'.format(interface) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#ifndef {{class|upper}}_H
#define {{class|upper}}_H

#include <QtCore>
#include <QtRemoteObjects>
#include "rep_{{module}}_source.h"

{% for property in interface.properties %}
{% if property.type.is_model and property.type.nested.is_complex %}
#include "{{property.type.nested|lower}}model.h"
{% endif %}
{% endfor %}
#include "variantmodel.h"

class {{class}} : public {{interface}}SimpleSource
{
    Q_OBJECT
{% for property in interface.properties if property.type.is_model %}
{% if property.type.nested.is_primitive %}
    Q_PROPERTY(VariantModel* {{property}} READ {{property}} CONSTANT)
{% else %}
    Q_PROPERTY({{property.type.nested|upperfirst}}Model* {{property}} READ {{property}} CONSTANT)
{% endif %}
{% endfor %}

public:
    explicit {{class}}(QObject *parent = nullptr);

{% for property in interface.properties if property.type.is_model %}
{% if property.type.nested.is_primitive %}
    virtual VariantModel* {{property}}() const;
{% else %}
    virtual {{property.type.nested|upperfirst}}Model* {{property}}() const;
{% endif %}
{% endfor %}

public Q_SLOTS:
{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation|parameters}});
{% endfor %}
private:
{% for property in interface.properties if property.type.is_model %}
{% if property.type.nested.is_primitive %}
    VariantModel* m_{{property}};
{% else %}
    {{property.type.nested|upperfirst}}Model* m_{{property}};
{% endif %}
{% endfor %}
};

#endif // {{class|upper}}_H
