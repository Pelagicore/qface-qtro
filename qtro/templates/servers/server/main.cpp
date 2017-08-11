/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include <QtCore>
#include <QtRemoteObjects>
#include "core.h"

{% for interface in module.interfaces %}
#include "{{interface|lower}}service.h"
{% endfor %}

{{module|using_ns}}

void registerModel(QRemoteObjectHostBase* host, QAbstractItemModel* model, const QString& name)
{
    if (!host or !model) {
        qWarning() << "no host or model given. Can not register model: " << name;
        return;
    }
    QVector<int> roles = model->roleNames().keys().toVector();
    host->enableRemoting(model, name, roles);
    qDebug() << "register model at: " << name;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QRemoteObjectRegistryHost* host = Core::instance()->host();

{% for interface in module.interfaces %}
    // create {{interface}} service
    QScopedPointer<{{interface}}Service> {{interface|lowerfirst}}Service(new {{interface}}Service);
    host->enableRemoting({{interface|lowerfirst}}Service.data(), "{{interface.qualified_name}}");
    qDebug() << "register service at: {{interface.qualified_name}}";
{% for property in interface.properties if property.type.is_model %}
    registerModel(host, {{interface|lowerfirst}}Service->{{property}}(), "{{property.qualified_name}}");
{% endfor %}

{% endfor %}
    return a.exec();
}
