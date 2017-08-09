#############################################################################
## This is an auto-generated file.
## Do not edit! All changes made to it will be lost.
#############################################################################

QT += qml quick
QT += remoteobjects
CONFIG += c++11

HEADERS += $$PWD/core.h
SOURCES += $$PWD/core.cpp

HEADERS += $$PWD/variantmodel.h
SOURCES += $$PWD/variantmodel.cpp


{% for interface in module.interfaces %}
# {{interface}}
HEADERS += $$PWD/{{interface|lower}}base.h
SOURCES += $$PWD/{{interface|lower}}base.cpp
HEADERS += $$PWD/{{interface|lower}}replica.h
SOURCES += $$PWD/{{interface|lower}}replica.cpp
{% endfor %}

{% for struct in module.structs %}
# {{struct}}
HEADERS += $$PWD/{{struct|lower}}.h
SOURCES += $$PWD/{{struct|lower}}.cpp
HEADERS += $$PWD/{{struct|lower}}model.h
SOURCES += $$PWD/{{struct|lower}}model.cpp
{% endfor %}

{% for enum in module.enums %}
HEADERS += $$PWD/{{enum|lower}}enum.h
{% endfor %}


