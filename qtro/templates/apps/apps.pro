TEMPLATE = subdirs

{% if features.scaffold %}
SUBDIRS += {{project|lower}}app
{% endif %}
