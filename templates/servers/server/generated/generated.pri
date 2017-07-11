QT += qml quick
QT += remoteobjects
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/{{interface|lower}}abstractsource.h
{% endfor %}
{% for struct in module.structs %}
HEADERS += $$PWD/{{struct|lower}}model.h
{% endfor %}
HEADERS += $$PWD/variantmodel.h

{% for interface in module.interfaces %}
SOURCES += $$PWD/{{interface|lower}}abstractsource.cpp
{% endfor %}
{% for struct in module.structs %}
SOURCES += $$PWD/{{struct|lower}}model.cpp
{% endfor %}
SOURCES += $$PWD/variantmodel.cpp

RESOURCES += $$SOURCE_DIR/shared/project.qrc