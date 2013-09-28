TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors

SOURCES += main.cpp \
    graphtask18.cpp \
    ../10/graph.cpp

HEADERS += \
    graphtask18.h

