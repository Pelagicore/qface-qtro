TEMPLATE = lib
TARGET = {{module|identifier}}
DESTDIR = $$BUILD_DIR/libs

CONFIG += staticlib
CONFIG += c++11

QT += qml
QT += quick
QT += remoteobjects

uri = {{module}}

{% for interface in module.interfaces %}
HEADERS += $$PWD/{{interface|lower}}.h
{% endfor %}

{% for interface in module.interfaces %}
SOURCES += $$PWD/{{interface|lower}}.cpp
{% endfor %}

include( $$PWD/generated/generated.pri )

REPC_REPLICA += $$SOURCE_DIR/shared/{{module}}.rep

RESOURCES += $$SOURCE_DIR/shared/project.qrc

OTHER_FILES += $$SOURCE_DIR/shared/{{module}}.rep
OTHER_FILES += $$SOURCE_DIR/shared/server.conf
OTHER_FILES += uselib.pri

