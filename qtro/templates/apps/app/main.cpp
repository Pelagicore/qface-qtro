#include <QtGui>
#include <QtQml>


{% for module in system.modules %}
{% for interface in module.interfaces %}
#include "{{interface|lower}}.h"
{% endfor %}
{% endfor %}

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

{% for module in system.modules %}
{% for interface in module.interfaces %}
    {{module|ns}}::{{interface}}::registerQmlTypes();
{% endfor %}
{% endfor %}

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}