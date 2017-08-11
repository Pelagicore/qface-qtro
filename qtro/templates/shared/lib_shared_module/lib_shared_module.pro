TEMPLATE = lib
TARGET = shared_{{module|identifier}}
DESTDIR = $$BUILD_DIR/libs

CONFIG += staticlib
CONFIG += c++11

QT += core
QT += qml
QT += remoteobjects

{% for struct in module.structs %}
# {{struct}}
HEADERS += $$PWD/{{struct|lower}}.h
SOURCES += $$PWD/{{struct|lower}}.cpp
{% endfor %}

{% for enum in module.enums %}
HEADERS += $$PWD/{{enum|lower}}enum.h
{% endfor %}


OTHER_FILES += usesharedlib_{{module|identifier}}.pri

