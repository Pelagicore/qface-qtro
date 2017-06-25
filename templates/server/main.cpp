#include <QtCore>
#include <QtRemoteObjects>

{% for interface in module.interfaces %}
#include "{{interface|lower}}service.h"
{% endfor %}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QRemoteObjectRegistryHost host(QUrl("local:{{module|lower|replace(".", "-")}}"));
{% for interface in module.interfaces %}

    {{interface}}Service {{interface|lowerfirst}}Service;
    host.enableRemoting(&{{interface|lowerfirst}}Service, "{{interface.qualified_name}}");
{% endfor %}

    return a.exec();
}
