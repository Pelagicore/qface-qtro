TEMPLATE = subdirs

{% if features.apps %}
SUBDIRS += apps
{% endif %}
SUBDIRS += clients
SUBDIRS += servers

{% if features.apps %}
apps.depends += clients
apps.depends += servers
{% endif %}
clients.depends += servers

include( {{project}}.pri )
