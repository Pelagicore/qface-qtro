QT += qml quick
QT += remoteobjects
CONFIG += c++11

{% for interface in module.interfaces %}
HEADERS += $$PWD/{{interface|lower}}abstractsource.h
# HEADERS += $$PWD/{{interface|lower}}sourceapi.h
{% endfor %}
{% for struct in module.structs %}
# HEADERS += $$PWD/{{struct|lower}}.h
HEADERS += $$PWD/{{struct|lower}}model.h
{% endfor %}
{% for enum in module.enums %}
# HEADERS += $$PWD/{{enum|lower}}.h
{% endfor %}
HEADERS += $$PWD/variantmodel.h

{% for interface in module.interfaces %}
SOURCES += $$PWD/{{interface|lower}}abstractsource.cpp
{% endfor %}
{% for struct in module.structs %}
# SOURCES += $$PWD/{{struct|lower}}.cpp
SOURCES += $$PWD/{{struct|lower}}model.cpp
{% endfor %}
SOURCES += $$PWD/variantmodel.cpp

RESOURCES += $$SOURCE_DIR/shared/project.qrc