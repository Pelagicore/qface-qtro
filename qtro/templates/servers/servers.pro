TEMPLATE = subdirs

{% for module in system.modules %}
SUBDIRS += {{module|identifier}}
{% endfor %}

scripts.path = $$BUILD_DIR
scripts.files = *.sh

INSTALLS += scripts

