#include <QtGui>
#include <QtQml>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}