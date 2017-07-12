TEMPLATE = lib

CONFIG += staticlib c++11
QT += qml quick remoteobjects
DESTDIR = $$BUILD_DIR/libs
TARGET = {{project}}


{%for module in system.modules %}
include(plugins/{{module|identifier}}/{{module|identifier}}.pri)
{% endfor %}

include( {{project}}.pri )
