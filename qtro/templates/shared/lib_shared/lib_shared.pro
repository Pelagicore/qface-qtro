TEMPLATE = lib
TARGET = shared
DESTDIR = $$BUILD_DIR/libs

CONFIG += staticlib
CONFIG += c++11

QT += core
QT += qml
QT += remoteobjects

RESOURCES += $$PWD/project.qrc

OTHER_FILES += $$PWD/server.conf

HEADERS += $$PWD/variantmodel.h
SOURCES += $$PWD/variantmodel.cpp

OTHER_FILES += usesharedlib.pri

