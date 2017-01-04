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
    descriptor.cpp \
    historygraph.cpp \
    historygraphnode.cpp

HEADERS += abstractvoronoidiagram.h \
    basicoperationprovider.h \
    descriptor.h \
    historygraph.h \
    historygraphnode.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
