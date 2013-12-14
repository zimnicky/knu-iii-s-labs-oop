QT       += core gui opengl

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lX11 -lGLU

SOURCES += \
    main.cpp \
    renderer.cpp \
    field.cpp \
    camera.cpp \
    apple.cpp

HEADERS += \
    renderer.h \
    field.h \
    camera.h \
    apple.h

RESOURCES += \
    textures.qrc
