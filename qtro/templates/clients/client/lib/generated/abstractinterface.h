{% set class = 'Abstract{0}'.format(interface) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtCore>
#include <QtRemoteObjects>

#include "rep_{{module|lower}}_replica.h"

{{interface|open_ns}}

class {{class}} : public QObject
{
    Q_OBJECT
{% for property in interface.properties %}
{% if property.type.is_model %}
    Q_PROPERTY(QAbstractItemModelReplica* {{property}} READ {{property}} CONSTANT)
{% else %}
    Q_PROPERTY({{property|returnType}} {{property}} READ {{property}} {% if not property.readonly %}WRITE set{{property|upperfirst}} {% endif %}{% if not property.const %}NOTIFY {{property}}Changed{% endif %})
{% endif %}
{% endfor %}

public:
    {{class}}(QObject *parent = nullptr);
    ~{{class}}();

public Q_SLOTS:
{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation.parameters|map('parameterType')|join(', ')}});
{% endfor %}

public:
{% for property in interface.properties if not property.type.is_model %}
    virtual void set{{property|upperfirst}}({{ property|parameterType }});
    virtual {{property|returnType}} {{property}}() const;
{% endfor %}
{% for property in interface.properties if property.type.is_model %}
    QAbstractItemModelReplica* {{property}}() const;
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
{% for property in interface.properties if property.type.is_model %}
    QScopedPointer<QAbstractItemModelReplica> m_{{property|lowerfirst}};
{% endfor %}
};

{{interface|close_ns}}

