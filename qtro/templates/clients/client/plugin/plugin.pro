TEMPLATE = lib
QT += qml remoteobjects
CONFIG += qt plugin c++11
DESTDIR = $$BUILD_DIR/imports/{{module|path}}
TARGET = {{module|identifier}}_plugin

uri = {{module}}

HEADERS += plugin.h
SOURCES += plugin.cpp

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$BUILD_DIR/imports/{{module|path}}/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}


LIBS += -L$$BUILD_DIR/libs -l{{module|identifier}}
INCLUDEPATH += $$PWD/../lib