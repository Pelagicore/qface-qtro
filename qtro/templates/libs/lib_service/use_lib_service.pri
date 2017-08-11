QT += core
QT += qml
QT += remoteobjects

LIBS += -L$$BUILD_DIR/libs
LIBS += -lservice_{{module|identifier}}

INCLUDEPATH += $$PWD

include( $$SOURCE_DIR/shared/lib_shared/use_lib_shared.pri )
include( $$SOURCE_DIR/shared/lib_shared_{{module|identifier}}/use_lib_shared_{{module|identifier}}.pri )
