QT += core
QT += qml
QT += remoteobjects

LIBS += -L$$BUILD_DIR/libs
LIBS += -lshared_{{module|identifier}}

INCLUDEPATH += $$PWD

