TEMPLATE = subdirs

{% for module in system.modules %}
SUBDIRS += {{module|lower|replace(".", "-")}}
{% endfor %}
