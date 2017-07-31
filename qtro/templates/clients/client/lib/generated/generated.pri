#############################################################################
## This is an auto-generated file.
## Do not edit! All changes made to it will be lost.
#############################################################################

QT += qml quick
QT += remoteobjects
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/{{interface|lower}}base.h
SOURCES += $$PWD/{{interface|lower}}base.cpp
HEADERS += $$PWD/{{interface|lower}}replica.h
SOURCES += $$PWD/{{interface|lower}}replica.cpp
{% endfor %}

{% for struct in module.structs %}
HEADERS += $$PWD/{{struct|lower}}.h
SOURCES += $$PWD/{{struct|lower}}.cpp
HEADERS += $$PWD/{{struct|lower}}proxymodel.h
SOURCES += $$PWD/{{struct|lower}}proxymodel.cpp
{% endfor %}


HEADERS += $$PWD/module.h
HEADERS += $$PWD/core.h
SOURCES += $$PWD/core.cpp

