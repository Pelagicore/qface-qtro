{% set class = '{0}AbstractSource'.format(interface) %}
#ifndef {{class|upper}}_H
#define {{class|upper}}_H

// This is an autogenerated file.
// Do not edit this file, any changes made will be lost the next time it is generated.

#include <QtCore>
#include <QtRemoteObjects>

{% for property in interface.properties %}
{% if property.type.is_model and property.type.nested.is_complex %}
#include "qml{{property.type.nested|lower}}model.h"
{% endif %}
{% endfor %}
#include "qmlvariantmodel.h"

class {{class}} : public QObject
{
  Q_OBJECT
  Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_TYPE, "{{interface}}")
  Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_SIGNATURE, "{{interface|hash}}")
{% for property in interface.properties if not property.type.is_model %}
  Q_PROPERTY({{property|returnType}} {{property}} READ {{property}} {% if not property.readonly %}WRITE set{{property|upperfirst}} {% endif %}{% if not property.const %}NOTIFY {{property}}Changed{% endif %})
{% endfor %}

public:
    explicit {{class}}(QObject *parent = nullptr);
public:
    virtual ~{{class}}();

{% for property in interface.properties %}
    virtual {{property|returnType}} {{property}}() const;
{% endfor %}
{% for property in interface.properties if not property.type.is_model %}
    virtual void set{{property|upperfirst}}({{property|parameterType}});
{% endfor %}

Q_SIGNALS:
{% for property in interface.properties %}
    void {{property}}Changed({{property|returnType}});
{% endfor %}
{% for signal in interface.signals %}
    void {{signal}}({{signal|parameters}});
{% endfor %}

public Q_SLOTS:
{% for property in interface.properties  if not property.type.is_model %}
    virtual void push{{property|upperfirst}}({{property|parameters}});
{% endfor %}
{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation|parameters}});
{% endfor %}

private:
{% for property in interface.properties if property.type.is_model and property.type.nested.is_complex %}
    Qml{{property.type.nested}}Model *m_{{property|lowerfirst}};
{% endfor %}
{% for property in interface.properties if property.type.is_model and property.type.nested.is_primitive %}
    QmlVariantModel * m_{{property|lowerfirst}};
{% endfor %}
    friend class QT_PREPEND_NAMESPACE(QRemoteObjectNode);
};



#endif // {{class|upper}}_H
