QT += qml quick
QT += remoteobjects
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/abstract{{interface|lower}}source.h
SOURCES += $$PWD/abstract{{interface|lower}}source.cpp
{% endfor %}

{% for struct in module.structs %}
HEADERS += $$PWD/{{struct|lower}}model.h
SOURCES += $$PWD/{{struct|lower}}model.cpp
{% endfor %}

HEADERS += $$PWD/variantmodel.h
SOURCES += $$PWD/variantmodel.cpp