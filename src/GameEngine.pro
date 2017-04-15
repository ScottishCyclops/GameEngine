#QT += core
#QT -= gui

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lGLEW -lSDL2

SOURCES += main.cpp            \
    engine/camera.cpp          \
    engine/display.cpp         \
    engine/game.cpp            \
    engine/scene.cpp           \
    engine/mesh/mesh.cpp       \
    engine/mesh/meshloader.cpp \
    engine/shader/shader.cpp   \
    engine/texture/texture.cpp \
    engine/utils/input.cpp     \
    engine/utils/transform.cpp \
    engine/utils/utils.cpp

HEADERS += libs.h              \
    engine/camera.h            \
    engine/display.h           \
    engine/game.h              \
    engine/scene.h             \
    engine/mesh/mesh.h         \
    engine/mesh/meshloader.h   \
    engine/shader/shader.h     \
    engine/texture/stb_image.h \
    engine/texture/texture.h   \
    engine/utils/input.h       \
    engine/utils/time.h        \
    engine/utils/transform.h   \
    engine/utils/utils.h
