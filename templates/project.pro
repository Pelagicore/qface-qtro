TEMPLATE = subdirs

SUBDIRS += plugins
SUBDIRS += servers

OTHER_FILES += .qmake.conf
{% for module in system.modules %}
OTHER_FILES += shared/{{module|identifier}}.rep
{% endfor %}