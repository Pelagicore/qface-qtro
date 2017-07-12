QT += core
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/{{interface|lower}}engine.h
SOURCES += $$PWD/{{interface|lower}}engine.cpp
{% endfor %}
