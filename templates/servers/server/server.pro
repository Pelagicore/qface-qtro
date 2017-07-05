TEMPLATE = app
QT += core remoteobjects
QT -= gui

CONFIG += c++11

DESTDIR = $$BUILD_DIR/bin
TARGET = {{module}}
CONFIG += console
CONFIG -= app_bundle

include(generated/generated.pri)

{% for interface in module.interfaces %}
HEADERS += {{interface|lower}}service.h
{% endfor %}

{% for interface in module.interfaces %}
SOURCES += {{interface|lower}}service.cpp
{% endfor %}
SOURCES += main.cpp


REPC_SOURCE += $$SOURCE_DIR/shared/{{module}}.rep
