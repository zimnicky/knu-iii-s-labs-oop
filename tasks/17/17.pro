TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors

SOURCES += main.cpp \
    graphtask17.cpp \
    ../10/graph.cpp

HEADERS += \
    graphtask17.h

