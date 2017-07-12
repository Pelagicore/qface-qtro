TEMPLATE = subdirs

SUBDIRS += plugins
SUBDIRS += servers
SUBDIRS += engines

servers.depends += engines

include( {{project}}.pri )