{% set class= '{0}Module'.format(module.module_name|upperfirst) %}


#include "{{class|lower}}.h"

QRemoteObjectNode* {{class}}::m_node(nullptr);


{{class}}::{{class}}()
{
}

void {{class}}::init()
{
    qDebug() << "{{class}}::init()";
    QSettings settings(":/server.conf", QSettings::IniFormat);
    settings.beginGroup("{{module}}");
    QUrl url = QUrl(settings.value("Registry", "local:{{module}}").toString());
    m_node = new QRemoteObjectNode(url);
    connect(m_node, &QRemoteObjectNode::error, this, &Core::reportError);
}

QRemoteObjectNode* {{class}}::node()
{
    qDebug() << "{{class}}::node()";
    init();
    Q_ASSERT(m_node);
    return m_node;
}

void {{class}}::reportError(QRemoteObjectNode::ErrorCode code)
{
    qDebug() << "Error: " << code;
}

void {{class}}::registerTypes(const char *uri)
{
{% for struct in module.structs %}
    qRegisterMetaType<{{struct}}>();
{% endfor %}

{% for interface in module.interfaces %}
    {{interface}}::registerTypes(uri, 1, 0);
{% endfor %}
}
