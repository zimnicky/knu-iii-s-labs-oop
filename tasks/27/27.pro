TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors

SOURCES += main.cpp \
    graphtask27.cpp \
    ../10/graph.cpp \
    ../17/graphtask17.cpp

HEADERS += \
    graphtask27.h \
    ../17/graphtask17.h \
    ../10/graph.h

