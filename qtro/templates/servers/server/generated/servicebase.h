{% set class = '{0}ServiceBase'.format(interface) %}
{% set models = interface.properties|selectattr('is_model')|list %}
{% set primitive_models = interface.properties|selectattr('is_primitive_model')|list %}
{% set complex_models = interface.properties|selectattr('is_complex_model')|list %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#ifndef {{class|upper}}_H
#define {{class|upper}}_H

#include <QtCore>
#include <QtRemoteObjects>
#include "rep_{{module}}_source.h"
{% for property in complex_models %}
#include "{{property.type.nested|lower}}model.h"
{% endfor %}
#include "variantmodel.h"

class {{interface}}Engine;

class {{class}} : public {{interface}}SimpleSource
{
    Q_OBJECT
{% for property in primitive_models %}
    Q_PROPERTY(VariantModel* {{property}} READ {{property}} CONSTANT)
{% endfor %}
{% for property in complex_models %}
    Q_PROPERTY({{property.type.nested|upperfirst}}Model* {{property}} READ {{property}} CONSTANT)
{% endfor %}

public:
    explicit {{class}}(QObject *parent = nullptr);

    {{interface}}Engine* engine() const;

{% for property in primitive_models %}
    virtual VariantModel* {{property}}() const;
{% endfor %}
{% for property in complex_models %}
    virtual {{property.type.nested|upperfirst}}Model* {{property}}() const;
{% endfor %}

public Q_SLOTS:
{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation|parameters}});
{% endfor %}
private:
{% for property in interface.properties %}
{% if property.is_primitive_model %}
    VariantModel* m_{{property}};
{% elif property.is_complex_model %}
    {{property.type.nested|upperfirst}}Model* m_{{property}};
{% endif %}
{% endfor %}
    {{interface}}Engine *m_engine;
};

#endif // {{class|upper}}_H
