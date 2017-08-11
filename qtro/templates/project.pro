TEMPLATE = subdirs

SUBDIRS += apps
SUBDIRS += servers
SUBDIRS += plugins
SUBDIRS += libs
SUBDIRS += shared

apps.depends += plugins
apps.depends += servers
apps.depends += libs
servers.depends += libs
plugins.depends += libs
libs.depends += shared

OTHER_FILES += .qmake.conf

