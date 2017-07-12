TEMPLATE = subdirs

{% for module in system.modules %}
SUBDIRS += {{module|identifier}}
{% endfor %}
