#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T22:49:31
#
#-------------------------------------------------

QT       -= gui

TARGET = lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += abstractvoronoidiagram.cpp \
    descriptor.cpp

HEADERS += abstractvoronoidiagram.h \
    basicoperationprovider.h \
    descriptor.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
