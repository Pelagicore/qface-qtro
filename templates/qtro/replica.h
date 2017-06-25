{% set class = '{0}Replica'.format(interface) %}

#ifndef REP_{{interface|upper}}_REPLICA_H
#define REP_{{interface|upper}}_REPLICA_H

#include <QtCore>
#include <QtRemoteObjects>


{% for interface in module.interfaces %}
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

{% endfor %}
Q_SIGNALS:
{% for property in interface.properties %}
    void {{property}}Changed({{property|returnType}});
{% endfor %}

public Q_SLOTS:
{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation|parameters}})
    {
        static int __repc_index = {{class}}::staticMetaObject.indexOfSlot("{{operation}}({{operation|parameters('returnType', False)}})");
        QVariantList __repc_args;
        send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
    }

{% endfor %}
private:
    friend class QT_PREPEND_NAMESPACE(QRemoteObjectNode);
};

{% endfor %}

#endif // REP_{{interface|upper}}_REPLICA_H
