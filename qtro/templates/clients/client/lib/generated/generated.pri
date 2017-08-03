#############################################################################
## This is an auto-generated file.
## Do not edit! All changes made to it will be lost.
#############################################################################

QT += qml quick
QT += remoteobjects
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/abstract{{interface|lower}}.h
{% endfor %}
HEADERS += $$PWD/core.h

{% for interface in module.interfaces %}
SOURCES += $$PWD/abstract{{interface|lower}}.cpp
{% endfor %}
SOURCES += $$PWD/core.cpp

