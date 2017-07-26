TEMPLATE = app
TARGET = {{project|lower}}app
DESTDIR = $$BUILD_DIR/bin

QT += qml
QT += quick

CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc
