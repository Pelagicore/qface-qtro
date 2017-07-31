{% set class = "Core" %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"

{{module|using_ns}}

{{class}}* {{class}}::s_instance(nullptr);

{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
    , m_node(nullptr)
{
    init();
}

void {{class}}::init()
{
    QSettings settings(":/server.conf", QSettings::IniFormat);
    settings.beginGroup("{{module}}");
    QUrl url = QUrl(settings.value("Registry", "local:{{module}}").toString());
    m_node = new QRemoteObjectNode(url);
    qDebug() << "{{class}}::{{class}}()";
    connect(m_node, &QRemoteObjectNode::error, this, &{{class}}::reportError);
    registerTypes();

}

{{class}}* {{class}}::instance()
{
    qDebug() << "{{class}}::instance()";
    if (!s_instance) {
        s_instance = new {{class}}(QCoreApplication::instance());
    }
    Q_ASSERT(s_instance);
    return s_instance;
}

QRemoteObjectNode* {{class}}::node() const
{
    qDebug() << "{{class}}::node()";
    Q_ASSERT(m_node);
    return m_node;
}

void {{class}}::registerTypes()
{
{% for struct in module.structs %}
    {{struct}}::registerTypes();
{% endfor %}
}

{% for struct in module.structs %}
{{struct}} {{class}}::create{{struct}}()
{
    return {{struct}}();
}
{% endfor %}

void {{class}}::reportError(QRemoteObjectNode::ErrorCode code)
{
    qDebug() << "Error: " << code;
}
