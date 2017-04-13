#QT += core
#QT -= gui

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lGLEW -lSDL2

SOURCES += main.cpp \
    engine/display.cpp \
    engine/game.cpp \
    engine/utils/input.cpp \
    engine/mesh/mesh.cpp\
    engine/utils/transform.cpp \
    engine/mesh/shader.cpp \
    engine/camera.cpp\
    engine/mesh/meshloader.cpp\
    engine/utils/utils.cpp \
    engine/scene.cpp

HEADERS += \
    engine/display.h \
    libs.h \
    engine/utils/time.h \
    engine/game.h \
    engine/utils/input.h \
    engine/mesh/mesh.h \
    engine/utils/transform.h \
    engine/mesh/shader.h \
    engine/camera.h \
    engine/mesh/meshloader.h \
    engine/utils/utils.h \
    engine/scene.h
