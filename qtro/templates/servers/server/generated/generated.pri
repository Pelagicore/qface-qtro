QT += qml quick
QT += remoteobjects
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/{{interface|lower}}servicebase.h
SOURCES += $$PWD/{{interface|lower}}servicebase.cpp
{% endfor %}

{% for struct in module.structs %}
HEADERS += $$PWD/{{struct|lower}}.h
SOURCES += $$PWD/{{struct|lower}}.cpp
HEADERS += $$PWD/{{struct|lower}}model.h
SOURCES += $$PWD/{{struct|lower}}model.cpp
{% endfor %}

HEADERS += $$PWD/core.h
SOURCES += $$PWD/core.cpp
HEADERS += $$PWD/variantmodel.h
SOURCES += $$PWD/variantmodel.cpp

OTHER_FILES += $$SOURCE_DIR/shared/server.conf

RESOURCES += $$SOURCE_DIR/shared/project.qrc

