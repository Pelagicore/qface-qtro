{% set class = '{0}Base'.format(interface) %}
{% set models = interface.properties|selectattr('is_model')|list %}
{% set primitive_models = interface.properties|selectattr('is_primitive_model')|list %}
{% set complex_models = interface.properties|selectattr('is_complex_model')|list %}
{% set properties = interface.properties|rejectattr('is_model')|list %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtCore>
#include <QtRemoteObjects>

#include "core.h"
#include "{{interface|lower}}replica.h"


{{interface|open_ns}}

class {{class}} : public QObject
{
    Q_OBJECT
{% for property in properties %}
    Q_PROPERTY({{property|returnType}} {{property}} READ {{property}} {% if not property.readonly %}WRITE set{{property|upperfirst}} {% endif %}{% if not property.const %}NOTIFY {{property}}Changed{% endif %})
{% endfor %}
{% for property in primitive_models %}
    Q_PROPERTY({{property|returnType}} {{property}} READ {{property}} CONSTANT)
{% endfor %}
{% for property in complex_models %}
    Q_PROPERTY({{property|returnType}} {{property}} READ {{property}} CONSTANT)
{% endfor %}
public:
    {{class}}(QObject *parent = nullptr);
    ~{{class}}();

public Q_SLOTS:
{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation.parameters|map('parameterType')|join(', ')}});
{% endfor %}

public:
{% for property in properties %}
    virtual void set{{property|upperfirst}}({{ property|parameterType }});
    virtual {{property|returnType}} {{property}}() const;
{% endfor %}
{% for property in primitive_models %}
     {{property|returnType}} {{property}}() const;
{% endfor %}
{% for property in complex_models %}
    {{property|returnType}}{{property}}() const;
{% endfor %}

Q_SIGNALS:
{% for signal in interface.signals %}
    void {{signal}}({{signal.parameters|map('parameterType')|join(', ')}});
{% endfor %}
{% for property in interface.properties if not property.type.is_model %}
    void {{property}}Changed();
{% endfor %}

protected:
    void setupConnections();

private:
    QScopedPointer<{{interface}}Replica> m_replica;
{% for property in models %}
    QScopedPointer<QAbstractItemModelReplica> m_{{property|lowerfirst}}Model;
{% endfor %}
{% for property in primitive_models %}
     {{property|returnType}} m_{{property}};
{% endfor %}
{% for property in complex_models %}
    {{property|returnType}} m_{{property}};
{% endfor %}
};

{{interface|close_ns}}

