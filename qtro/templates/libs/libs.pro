TEMPLATE = subdirs

{% for module in system.modules %}
SUBDIRS += lib_client_{{module|identifier}}
{% endfor %}
{% for module in system.modules %}
SUBDIRS += lib_service_{{module|identifier}}
{% endfor %}
