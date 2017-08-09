TEMPLATE = subdirs

SUBDIRS += apps
SUBDIRS += servers
SUBDIRS += plugins
SUBDIRS += libs

apps.depends += plugins
apps.depends += servers
apps.depends += libs
servers.depends += libs
plugins.depends += libs

OTHER_FILES += .qmake.conf

