TEMPLATE = app
QT += core remoteobjects
QT -= gui

CONFIG += c++11

DESTDIR = $$BUILD_DIR/bin
TARGET = {{module}}
CONFIG += console
CONFIG -= app_bundle

include(gen/gen.pri)

{% for interface in module.interfaces %}
HEADERS += {{interface|lower}}service.h
SOURCES += {{interface|lower}}service.cpp
{% endfor %}

SOURCES += main.cpp


REPC_SOURCE += $$SOURCE_DIR/shared/{{module|identifier}}.rep
