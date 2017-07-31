QT += qml quick remoteobjects
CONFIG += qt plugin c++11
uri = {{module}}

{% for interface in module.interfaces %}
HEADERS += $$PWD/{{interface|lower}}.h
{% endfor %}

{% for interface in module.interfaces %}
SOURCES += $$PWD/{{interface|lower}}.cpp
{% endfor %}

include( $$PWD/generated/generated.pri )

RESOURCES += $$SOURCE_DIR/shared/project.qrc
