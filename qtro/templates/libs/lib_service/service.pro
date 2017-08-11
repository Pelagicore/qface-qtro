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

include( $$SOURCE_DIR/shared/lib_shared/use_lib_shared.pri )
include( $$SOURCE_DIR/shared/lib_shared_{{module|identifier}}/use_lib_shared_{{module|identifier}}.pri )

OTHER_FILES += use_lib_service_{{module|identifier}}.pri
