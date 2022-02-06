QT       += \
    core gui \
    core gui opengl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS += -lGLU

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    fpp_camera.cpp \
    fpp_movement.cpp \
    generation_menu.cpp \
    grid_layout.cpp \
    hydro.cpp \
    interface_controller.cpp \
    loading_menu.cpp \
    main.cpp \
    noise.cpp \
    scene_menu.cpp \
    super.cpp \
    terrain.cpp \
    world.cpp \
    world_menu.cpp

HEADERS += \
    fpp_camera.h \
    fpp_movement.h \
    generation_menu.h \
    grid_layout.h \
    hydro.h \
    interface_controller.h \
    loading_menu.h \
    main.h \
    noise.h \
    scene_menu.h \
    super.h \
    terrain.h \
    world.h \
    connections.h \
    world_menu.h

FORMS += \
    main.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
