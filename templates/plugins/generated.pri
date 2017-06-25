{# Copyright (c) Pelagicore AB 2016 #}
#############################################################################
## This is an auto-generated file.
## Do not edit! All changes made to it will be lost.
#############################################################################

QT += qml quick
QT += remoteobjects
CONFIG += c++11

HEADERS += $$PWD/qml{{module.module_name|lower}}module.h
{% for interface in module.interfaces %}
HEADERS += $$PWD/qmlabstract{{interface|lower}}.h
{% endfor %}
{% for struct in module.structs %}
HEADERS += $$PWD/qml{{struct|lower}}.h
HEADERS += $$PWD/qml{{struct|lower}}model.h
{% endfor %}
HEADERS += $$PWD/qmlvariantmodel.h


SOURCES += $$PWD/qml{{module.module_name|lower}}module.cpp
{% for interface in module.interfaces %}
SOURCES += $$PWD/qmlabstract{{interface|lower}}.cpp
{% endfor %}
{% for struct in module.structs %}
SOURCES += $$PWD/qml{{struct|lower}}.cpp
SOURCES += $$PWD/qml{{struct|lower}}model.cpp
{% endfor %}
SOURCES += $$PWD/qmlvariantmodel.cpp


