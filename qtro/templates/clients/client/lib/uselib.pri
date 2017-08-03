QT += core
QT += qml
QT += remoteobjects

LIBS *= -L $$BUILD_DIR/libs
LIBS += -l {{module|identifier}}

INCLUDEPATH += $$PWD
INCLUDEPATH += $$shadowed($$PWD)
