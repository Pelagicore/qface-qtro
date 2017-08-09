{% for struct in module.structs %}
# {{struct}}
HEADERS += $$PWD/{{struct|lower}}.h
SOURCES += $$PWD/{{struct|lower}}.cpp
{% endfor %}

{% for enum in module.enums %}
HEADERS += $$PWD/{{enum|lower}}enum.h
{% endfor %}

INCLUDEPATH += $$PWD
