/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "core.h"


{% for interface in module.interfaces %}
#include "../{{interface|lower}}.h"
{% endfor %}

{{module|using_ns}}

Core* Core::s_instance(nullptr);

Core::Core(QObject *parent)
    : QObject(parent)
    , m_node(nullptr)
{
    QSettings settings(":/server.conf", QSettings::IniFormat);
    settings.beginGroup("{{module}}");
    QUrl url = QUrl(settings.value("Registry", "local:{{module}}").toString());
    m_node = new QRemoteObjectNode(url);
    qDebug() << "Core::Core()";
    connect(m_node, &QRemoteObjectNode::error, this, &Core::reportError);

}

Core* Core::instance()
{
    qDebug() << "Core::instance()";
    if (!s_instance) {
        s_instance = new Core(QCoreApplication::instance());
    }
    Q_ASSERT(s_instance);
    return s_instance;
}

QRemoteObjectNode* Core::node() const
{
    qDebug() << "Core::node()";
    Q_ASSERT(m_node);
    return m_node;
}

void Core::reportError(QRemoteObjectNode::ErrorCode code)
{
    qDebug() << "Error: " << code;
}

void Core::registerTypes(const char *uri)
{
{% for interface in module.interfaces %}
    {{interface}}::registerQmlTypes(uri, 1, 0);
{% endfor %}
}
