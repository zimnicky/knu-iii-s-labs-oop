TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors

SOURCES += main.cpp \
    ../10/graph.cpp \
    graphtask15.cpp

HEADERS += \
    ../10/graph.h \
    graphtask15.h

