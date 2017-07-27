TEMPLATE = app
TARGET = {{project|lower}}app
DESTDIR = $$BUILD_DIR/bin

QT += qml
QT += quick

CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

{% for module in system.modules %}
include( $$SOURCE_DIR/clients/{{module|identifier}}/lib/uselib.pri )
{% endfor %}
