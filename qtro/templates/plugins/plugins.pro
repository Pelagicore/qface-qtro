TEMPLATE = subdirs

{% for module in system.modules %}
SUBDIRS += plugin_{{module|identifier}}
{% endfor %}