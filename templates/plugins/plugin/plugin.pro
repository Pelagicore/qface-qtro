TEMPLATE = lib
QT += qml quick remoteobjects
CONFIG += qt plugin c++11
DESTDIR = $$BUILD_DIR/imports/{{module.name_parts|join('/')}}
TARGET = {{module|lower}}

uri = {{module}}

HEADERS += plugin.h
SOURCES += plugin.cpp

include( {{module|identifier}}.pri )

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$BUILD_DIR/imports/{{module.name_parts|join('/')}}/qmldir
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
