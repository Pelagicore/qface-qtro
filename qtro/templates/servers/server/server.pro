TEMPLATE = app
QT += core remoteobjects
QT -= gui

CONFIG += c++11

DESTDIR = $$BUILD_DIR/bin
TARGET = {{module}}_server
CONFIG += console
macos {
    CONFIG -= app_bundle
}

SOURCES += main.cpp
HEADERS += {{module.name|lower}}engine.h
SOURCES += {{module.name|lower}}engine.cpp

{% for interface in module.interfaces %}
HEADERS += {{interface|lower}}service.h
SOURCES += {{interface|lower}}service.cpp
{% endfor %}

include( $$SOURCE_DIR/libs/lib_service_{{module|identifier}}/useservicelib_{{module|identifier}}.pri )



