QT += qml quick
QT += remoteobjects
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/{{interface|lower}}abstractsource.h
{% endfor %}
{% for struct in module.structs %}
HEADERS += $$PWD/qml{{struct|lower}}.h
HEADERS += $$PWD/qml{{struct|lower}}model.h
{% endfor %}
HEADERS += $$PWD/qmlvariantmodel.h

{% for interface in module.interfaces %}
SOURCES += $$PWD/{{interface|lower}}abstractsource.cpp
{% endfor %}
{% for struct in module.structs %}
SOURCES += $$PWD/qml{{struct|lower}}.cpp
SOURCES += $$PWD/qml{{struct|lower}}model.cpp
{% endfor %}
SOURCES += $$PWD/qmlvariantmodel.cpp