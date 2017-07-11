TEMPLATE = lib

CONFIG += staticlib c++11
QT += core
DESTDIR = $$BUILD_DIR/libs
TARGET = {{module|identifier}}_engine



include( {{module|identifier}}.pri )
