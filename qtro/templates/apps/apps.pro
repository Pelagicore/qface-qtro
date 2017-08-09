TEMPLATE = subdirs

{% if 'apps' in features %}
SUBDIRS += demoapp
{% endif %}
