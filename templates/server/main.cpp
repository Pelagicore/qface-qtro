#include <QtCore>
#include <QtRemoteObjects>

{% for interface in module.interfaces %}
#include "{{interface|lower}}service.h"
{% endfor %}
// {% for struct in module.structs %}
// #include "generated/{{struct|lower}}.h"
// {% endfor %}
// {% for enum in module.enums %}
// #include "generated/{{enum|lower}}.h"
// {% endfor %}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QRemoteObjectRegistryHost host(QUrl("local:{{module}}"));
    qDebug() << "registry at: " << host.registryUrl().toString();

{% for interface in module.interfaces %}
    QScopedPointer<{{interface}}Service> {{interface|lowerfirst}}Service(new {{interface}}Service);
    host.enableRemoting({{interface|lowerfirst}}Service.data(), "{{interface.qualified_name}}");
    qDebug() << "service at: {{interface.qualified_name}}";
{% for property in interface.properties if property.type.is_model %}
    {
        QAbstractItemModel* model = {{interface|lowerfirst}}Service->{{property}}();
        Q_ASSERT(model);
        QVector<int> roles = model->roleNames().keys().toVector();
        host.enableRemoting(model, "{{property.qualified_name}}", roles);
        qDebug() << "model at: {{property.qualified_name}}";
    }
{% endfor %}

{% endfor %}

    return a.exec();
}
