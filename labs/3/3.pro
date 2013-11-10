TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    graph.cpp

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors -pthread
LIBS += -pthread

HEADERS += \
    graph.h
