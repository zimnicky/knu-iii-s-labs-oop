TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors

SOURCES += main.cpp \
    opncalculator.cpp

HEADERS += \
    opncalculator.h

