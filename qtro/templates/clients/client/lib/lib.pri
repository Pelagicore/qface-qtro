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

REPC_REPLICA += $$SOURCE_DIR/shared/{{module}}.rep

RESOURCES += $$SOURCE_DIR/shared/project.qrc
