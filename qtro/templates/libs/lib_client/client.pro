TEMPLATE = lib
TARGET = client_{{module|identifier}}
DESTDIR = $$BUILD_DIR/libs

CONFIG += staticlib
CONFIG += c++11

QT += core
QT += qml
QT += remoteobjects

HEADERS += core.h
SOURCES += core.cpp

{% for interface in module.interfaces %}
HEADERS += {{interface|lower}}.h
SOURCES += {{interface|lower}}.cpp
HEADERS += {{interface|lower}}replica.h
SOURCES += {{interface|lower}}replica.cpp

{% endfor %}

{% for struct in module.structs %}
HEADERS += {{struct|lower}}model.h
SOURCES += {{struct|lower}}model.cpp
{% endfor %}

include( $$SOURCE_DIR/shared/lib_shared/use_lib_shared.pri )
include( $$SOURCE_DIR/shared/lib_shared_{{module|identifier}}/use_lib_shared_{{module|identifier}}.pri )

OTHER_FILES += use_lib_client_{{module|identifier}}.pri

