{% set class = "Core" %}
{% set cat = 'lib_service_{0}'.format(module|identifier) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{class|lower}}.h"


Q_LOGGING_CATEGORY({{cat}}, "lib.service.{{module}}")


{{module|using_ns}}

{{class}}* {{class}}::s_instance(nullptr);

{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
    , m_host(nullptr)
{
    qCDebug({{cat}}) << "{{class}}::{{class}}()";
    init();
}

{{class}}::~{{class}}()
{
}

void {{class}}::init()
{
    qCDebug({{cat}}) << "{{class}}::init()";
    QSettings settings(":/server.conf", QSettings::IniFormat);
    settings.beginGroup("{{module}}");
    QUrl url = QUrl(settings.value("Registry", "local:{{module}}").toString());
    m_host = new QRemoteObjectRegistryHost(url);

    qDebug() << "registry at: " << m_host->registryUrl().toString();
    connect(m_host, &QRemoteObjectNode::error, this, &{{class}}::reportError);
    registerTypes();

}

{{class}}* {{class}}::instance()
{
    qCDebug({{cat}}) << "{{class}}::instance()";
    if (!s_instance) {
        s_instance = new {{class}}(QCoreApplication::instance());
    }
    Q_ASSERT(s_instance);
    return s_instance;
}

QRemoteObjectRegistryHost* {{class}}::host() const
{
    qCDebug({{cat}}) << "{{class}}::host()";
    Q_ASSERT(m_host);
    return m_host;
}

void {{class}}::registerTypes(const char* uri)
{
{% for struct in module.structs %}
    {{struct}}::registerTypes(uri);
{% endfor %}
{% for enum in module.enums %}
    {{enum}}Enum::registerTypes(uri);
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
    qCWarning({{cat}}) << "Error: " << code;
}
