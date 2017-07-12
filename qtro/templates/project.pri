OTHER_FILES += .qmake.conf
{% for module in system.modules %}
OTHER_FILES += shared/{{module}}.rep
{% endfor %}