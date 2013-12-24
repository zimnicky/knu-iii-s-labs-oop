TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    value.cpp \
    program.cpp \
    operations.cpp \
    parser.cpp

HEADERS += \
    variablestorage.h \
    value.h \
    program.h \
    operations.h \
    parser.h \
    tree.h \
    bor.h

