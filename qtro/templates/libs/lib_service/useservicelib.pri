QT += core
QT += qml
QT += remoteobjects

LIBS += -L$$BUILD_DIR/libs
LIBS += -lservice_{{module|identifier}}

INCLUDEPATH += $$PWD

include( $$SOURCE_DIR/shared/shared.pri )
include( $$SOURCE_DIR/shared/shared_{{module|identifier}}/shared_{{module|identifier}}.pri )
