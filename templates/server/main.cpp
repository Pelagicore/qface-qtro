#include <QtCore>
#include <QtRemoteObjects>

{% for interface in module.interfaces %}
#include "{{interface|lower}}service.h"
{% endfor %}
{% for struct in module.structs %}
#include "generated/{{struct|lower}}.h"
{% endfor %}
{% for enum in module.enums %}
#include "generated/{{enum|lower}}.h"
{% endfor %}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QRemoteObjectRegistryHost host(QUrl("local:{{module}}"));
    qDebug() << "start registry at: " << host.registryUrl().toString();

{% for struct in module.structs %}
    {{struct}}::registerTypes();
{% endfor %}
{% for enum in module.enums %}
    {{enum}}::registerTypes();
{% endfor %}

{% for interface in module.interfaces %}

    QScopedPointer<{{interface}}Service> {{interface|lowerfirst}}Service(new {{interface}}Service);
    host.enableRemoting({{interface|lowerfirst}}Service.data(), "{{interface.qualified_name}}");
    qDebug() << "start service at: {{interface.qualified_name}}";
{% endfor %}

    return a.exec();
}
