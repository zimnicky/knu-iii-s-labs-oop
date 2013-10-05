TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors
LIBS += -lX11 -ldl

SOURCES += main.cpp

