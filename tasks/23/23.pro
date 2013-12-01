TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors

SOURCES += main.cpp \
    menu.cpp \
    table.cpp

HEADERS += \
    menu.h \
    table.h

