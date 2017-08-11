TEMPLATE = lib
TARGET = service_{{module|identifier}}
DESTDIR = $$BUILD_DIR/libs

CONFIG += staticlib
CONFIG += c++11

QT += core
QT += qml
QT += remoteobjects

HEADERS += $$PWD/core.h
SOURCES += $$PWD/core.cpp

{% for interface in module.interfaces %}
HEADERS += $$PWD/{{interface|lower}}service.h
{% endfor %}

{% for struct in module.structs %}
HEADERS += $$PWD/{{struct|lower}}model.h
SOURCES += $$PWD/{{struct|lower}}model.cpp
{% endfor %}

include( $$SOURCE_DIR/shared/shared.pri )
include( $$SOURCE_DIR/shared/shared_{{module|identifier}}/shared_{{module|identifier}}.pri )

OTHER_FILES += useservicelib_{{module|identifier}}.pri
