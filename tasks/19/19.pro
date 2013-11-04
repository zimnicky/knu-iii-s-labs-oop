TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors

SOURCES += main.cpp \
    graph.cpp \
    disjointset.cpp

HEADERS += \
    graph.h \
    disjointset.h

