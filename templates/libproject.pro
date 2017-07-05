TEMPLATE = lib

CONFIG += staticlib c++11
QT += qml quick remoteobjects
DESTDIR = $$BUILD_DIR/libs
TARGET = {{project}}


{%for module in system.modules %}
include(plugins/{{module|lower|replace(".", "-")}}/{{module|lower|replace(".", "-")}}.pri)
{% endfor %}

include( {{project}}.pri )
