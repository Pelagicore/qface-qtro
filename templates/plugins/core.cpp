#include "core.h"


Core* Core::s_instance(nullptr);

Core::Core(QObject *parent)
    : QObject(parent)
    , m_node(new QRemoteObjectNode(QUrl(QStringLiteral("local:{{module}}"))))
{
}

Core* Core::instance()
{
    if (!s_instance) {
        new Core(QCoreApplication::instance());
    }
    return s_instance;
}

QRemoteObjectNode* Core::node() const
{
    return m_node;
}