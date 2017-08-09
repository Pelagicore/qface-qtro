{% set class = '{0}Engine'.format(module.name|upperfirst) %}
#include "{{class|lower}}.h"

{{module|using_ns}}

{{class}}* {{class}}::s_instance(nullptr);

{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
{
}

{{class}}::~{{class}}()
{
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
