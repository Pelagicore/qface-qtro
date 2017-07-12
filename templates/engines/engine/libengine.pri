QT += core

LIBS += -L$$BUILD_DIR/libs -l{{module|identifier}}_engine
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
PRE_TARGETDEPS += $$BUILD_DIR/libs/{{module|identifier}}_engine
