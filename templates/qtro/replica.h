{% set class = '{0}Replica'.format(interface) %}

#ifndef {{interface|upper}}REPLICA_H
#define {{interface|upper}}REPLICA_H

#include <QtCore>
#include <QtRemoteObjects>

{% for property in interface.properties %}
{% if property.type.is_model and property.type.nested.is_complex %}
#include "{{property.type.nested|lower}}model.h"
{% endif %}
{% endfor %}
#include "variantmodel.h"
{% for struct in module.structs %}
#include "{{struct|lower}}.h"
{% endfor %}
{% for enum in module.enums %}
#include "{{enum|lower}}.h"
{% endfor %}


class {{class}} : public QRemoteObjectReplica
{
    Q_OBJECT
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_TYPE, "{{interface}}")
    Q_CLASSINFO(QCLASSINFO_REMOTEOBJECT_SIGNATURE, "{{interface|hash}}")
{% for property in interface.properties %}
    Q_PROPERTY({{property|returnType}} {{property}} READ {{property}} {% if not property.readonly %}WRITE set{{property|upperfirst}} {% endif %}{% if not property.const %}NOTIFY {{property}}Changed{% endif %})
{% endfor %}
public:
    {{class}}() : QRemoteObjectReplica() { initialize(); }

private:
    {{class}}(QRemoteObjectNode *node, const QString &name = QString())
        : QRemoteObjectReplica(ConstructWithNode)
        { initializeNode(node, name); }

    void initialize()
    {
        QVariantList properties;
        properties.reserve({{interface.properties|length}});
{% for property in interface.properties %}
        properties << QVariant::fromValue({{property|defaultValue}});
{% endfor %}
        setProperties(properties);
    }


public:
    virtual ~{{class}}() {}

{% for property in interface.properties %}
    {{property|returnType}} {{property}}() const
    {
      const QVariant variant = propAsVariant({{loop.index0}});
      if (!variant.canConvert<{{property|returnType}}>()) {
          qWarning() << "QtRO cannot convert the property on to type {{property|returnType}}";
      }
      return variant.value<{{property|returnType}}>();
    }

    void set{{property|upperfirst}}({{property|parameters}})
    {
        push{{property|upperfirst}}({{property}});
    }

{% endfor %}
Q_SIGNALS:
{% for property in interface.properties %}
    void {{property}}Changed({{property|returnType}});
{% endfor %}
{% for signal in interface.signals %}
    void {{signal}}({{signal|parameters}});
{% endfor %}

public Q_SLOTS:
{% for property in interface.properties %}
    void push{{property|upperfirst}}({{property|parameters}})
    {
        static int __repc_index = {{class}}::staticMetaObject.indexOfSlot("{{property}}({{operation|parameters('returnType', False)}})");
        QVariantList __repc_args;
        __repc_args << QVariant::fromValue({{property}});
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }
{% endfor %}

{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation|parameters}})
    {
        static int __repc_index = {{class}}::staticMetaObject.indexOfSlot("{{operation}}({{operation|parameters('returnType', False)}})");
        QVariantList __repc_args;
{% for parameter in operation.parameters %}
        __repc_args << QVariant::fromValue({{parameter}});
{% endfor %}
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }

{% endfor %}
private:
    friend class QT_PREPEND_NAMESPACE(QRemoteObjectNode);
};

#endif // {{interface|upper}}REPLICA_H
