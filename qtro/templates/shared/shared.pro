TEMPLATE = subdirs

SUBDIRS += lib_shared

{% for module in system.modules %}
SUBDIRS += lib_shared_{{module|identifier}}
{% endfor %}
