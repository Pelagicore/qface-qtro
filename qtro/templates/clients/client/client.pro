TEMPLATE = subdirs

SUBDIRS += lib
SUBDIRS += plugin

plugin.depends += lib

include( $$PWD/docs/docs.pri )
