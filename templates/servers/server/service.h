{% import "qface/qtcpp.j2" as cpp %}
{% set class = '{0}Service'.format(interface) %}

#ifndef {{interface|upper}}_SERVICE_H
#define {{interface|upper}}_SERVICE_H

#include <QtCore>

#include "gen/abstract{{interface|lower}}source.h"


class {{class}} : public Abstract{{interface}}Source
{
    Q_OBJECT
public:
    explicit {{class}}(QObject *parent=nullptr);

{% for property in interface.properties %}
{% if property.type.is_model %}
    virtual QAbstractItemModel* {{property}}() const override;
{% else %}
    virtual {{property|qt.returnType}} {{property}}() const override;
    virtual void set{{property|upperfirst}}({{property|qt.signature}} {{property}}) override;
{% endif %}
{% endfor %}

{% for operation in interface.operations %}
    virtual {{operation|qt.returnType}} {{operation}}({{operation|qt.parameters}}) override;
{% endfor %}
private:
{% for property in interface.properties%}
{% if property.type.is_model and property.type.nested.is_primitive %}
    VariantModel* m_{{property}};
{% elif property.type.is_model and property.type.nested.is_complex %}
    {{property.type.nested|upperfirst}}Model* m_{{property}};
{% else %}
    {{property|qt.returnType}} m_{{property}};
{% endif %}
{% endfor %}
};

#endif // {{interface|upper}}_SERVICE_H
