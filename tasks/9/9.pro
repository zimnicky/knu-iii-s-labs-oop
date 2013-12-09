TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -errors

SOURCES += main.cpp \
    graphtask9.cpp \
    ../27/graphtask27.cpp \
    ../17/graphtask17.cpp \
    ../10/graph.cpp

HEADERS += \
    graphtask9.h \
    ../27/graphtask27.h \
    ../17/graphtask17.h \
    ../10/graph.h

OTHER_FILES += \
    ../10/10.pro

