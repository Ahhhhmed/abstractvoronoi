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
    historygraphnode.cpp \
    graphvisitor.cpp \
    edge.cpp \
    vertex.cpp \
    planargraph.cpp

HEADERS += abstractvoronoidiagram.h \
    basicoperationprovider.h \
    descriptor.h \
    historygraph.h \
    historygraphnode.h \
    graphvisitor.h \
    edge.h \
    vertex.h \
    planargraph.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
