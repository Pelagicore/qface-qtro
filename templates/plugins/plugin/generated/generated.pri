{# Copyright (c) Pelagicore AB 2016 #}
#############################################################################
## This is an auto-generated file.
## Do not edit! All changes made to it will be lost.
#############################################################################

QT += qml quick
QT += remoteobjects
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/abstract{{interface|lower}}.h
# HEADERS += $$PWD/{{interface|lower}}replica.h
{% endfor %}
{% for struct in module.structs %}
# HEADERS += $$PWD/{{struct|lower}}.h
# HEADERS += $$PWD/{{struct|lower}}model.h
{% endfor %}
{% for enum in module.enums %}
# HEADERS += $$PWD/{{enum|lower}}.h
{% endfor %}
# HEADERS += $$PWD/variantmodel.h
HEADERS += $$PWD/core.h


{% for interface in module.interfaces %}
SOURCES += $$PWD/abstract{{interface|lower}}.cpp
{% endfor %}
{% for struct in module.structs %}
# SOURCES += $$PWD/{{struct|lower}}.cpp
# SOURCES += $$PWD/{{struct|lower}}model.cpp
{% endfor %}
# SOURCES += $$PWD/variantmodel.cpp
SOURCES += $$PWD/core.cpp

