#############################################################################
## This is an auto-generated file.
## Do not edit! All changes made to it will be lost.
#############################################################################

QT += qml quick
QT += remoteobjects
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/abstract{{interface|lower}}.h
SOURCES += $$PWD/abstract{{interface|lower}}.cpp
{% endfor %}

{% for struct in module.structs %}
HEADERS += $$PWD/{{struct|lower}}.h
SOURCES += $$PWD/{{struct|lower}}.cpp
HEADERS += $$PWD/{{struct|lower}}modelproxy.h
SOURCES += $$PWD/{{struct|lower}}modelproxy.cpp
{% endfor %}


HEADERS += $$PWD/core.h
SOURCES += $$PWD/core.cpp

