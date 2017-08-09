{% set class = '{0}Replica'.format(interface) %}
{% set properties = interface.properties|rejectattr('is_model')|list %}

#include "{{class|lower}}.h"

{{module|using_ns}}

{{class}}::{{class}}()
    : QRemoteObjectReplica()
{
    initialize();
}

{{class}}::{{class}}(QRemoteObjectNode *node, const QString &name)
    : QRemoteObjectReplica(ConstructWithNode)
{
    initializeNode(node, name);
}

{{class}}::~{{class}}()
{
}

{% for property in properties %}
{{property|returnType}} {{class}}::{{property}}() const
{
    const QVariant variant = propAsVariant({{loop.index0}});
    if (!variant.canConvert<{{property|returnType}}>()) {
      qWarning() << "QtRO cannot convert the property on to type {{property|returnType}}";
    }
    return variant.value<{{property|returnType}}>();
}

void {{class}}::set{{property|upperfirst}}({{property|parameters}})
{
    push{{property|upperfirst}}({{property}});
}

{% endfor %}
{% for property in properties %}
void {{class}}::push{{property|upperfirst}}({{property|parameters}})
{
    static int __repc_index = {{class}}::staticMetaObject.indexOfSlot("{{property}}({{operation|parameters('returnType', False)}})");
    QVariantList __repc_args;
    __repc_args << QVariant::fromValue({{property}});
    send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
}

{% endfor %}
{% for operation in interface.operations %}
{{operation|returnType}} {{class}}::{{operation}}({{operation|parameters}})
{
    static int __repc_index = {{class}}::staticMetaObject.indexOfSlot("{{operation}}({{operation|parameters('returnType', False)}})");
    QVariantList __repc_args;
{% for parameter in operation.parameters %}
    __repc_args << QVariant::fromValue({{parameter}});
{% endfor %}
    send(QMetaObject::InvokeMetaMethod, __repc_index, __repc_args);
}

{% endfor %}
void {{class}}::initialize()
{
    QVariantList properties;
    properties.reserve({{properties|length}});
{% for property in properties %}
    properties << QVariant::fromValue({{property|defaultValue}});
{% endfor %}
    setProperties(properties);
}

