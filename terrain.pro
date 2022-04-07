QT       += \
    core gui \
    core gui opengl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS += -lGLU

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    fpp_camera.cpp \
    grid_layout.cpp \
    hydro.cpp \
    hydro2.cpp \
    interface_controller.cpp \
    interface_eroded_heightmap_preview.cpp \
    interface_generation_menu.cpp \
    interface_header.cpp \
    interface_heightmap_preview.cpp \
    interface_hydro_parameters_menu.cpp \
    interface_noise_layer.cpp \
    interface_noise_layers.cpp \
    interface_noise_parameters_menu.cpp \
    interface_scene_menu.cpp \
    interface_splash_screen.cpp \
    interface_terrain_parameters_menu.cpp \
    loading_menu.cpp \
    main.cpp \
    noise.cpp \
    noise_controller.cpp \
    noise_layer.cpp \
    super.cpp \
    terrain.cpp \
    world.cpp \
    world_menu.cpp

HEADERS += \
    fpp_camera.h \
    grid_layout.h \
    hydro.h \
    hydro2.h \
    interface_controller.h \
    interface_eroded_heightmap_preview.h \
    interface_generation_menu.h \
    interface_header.h \
    interface_heightmap_preview.h \
    interface_hydro_parameters_menu.h \
    interface_noise_layer.h \
    interface_noise_layers.h \
    interface_noise_parameters_menu.h \
    interface_scene_menu.h \
    interface_splash_screen.h \
    interface_terrain_parameters_menu.h \
    loading_menu.h \
    main.h \
    noise.h \
    noise_controller.h \
    noise_layer.h \
    super.h \
    terrain.h \
    world.h \
#    connections.h \
    world_menu.h

FORMS += \
    main.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
