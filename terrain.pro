QT       += \
    core gui \
    core gui opengl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 \
          warn_off

linux-g++ {
    QMAKE_CXXFLAGS_WARN_ON = -Wall -Wextra -Wno-enum-compare
}

LIBS += -lGLU

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    fpp_camera.cpp \
    hydro.cpp \
    hydro_flux.cpp \
    hydro_map.cpp \
    hydro_velocity.cpp \
    interface_controller.cpp \
    interface_double_slider.cpp \
    interface_eroded_heightmap_preview.cpp \
    interface_generation_menu.cpp \
    interface_heightmap_preview.cpp \
    interface_hydro_parameters_menu.cpp \
    interface_noise_layer.cpp \
    interface_noise_layers.cpp \
    interface_noise_parameters_menu.cpp \
    interface_splash_screen.cpp \
    interface_terrain_parameters_menu.cpp \
    main.cpp \
    noise_layer.cpp \
    terrain.cpp \
    world.cpp

HEADERS += \
    fpp_camera.h \
    hydro.h \
    hydro_flux.h \
    hydro_map.h \
    hydro_velocity.h \
    interface_controller.h \
    interface_double_slider.h \
    interface_eroded_heightmap_preview.h \
    interface_generation_menu.h \
    interface_heightmap_preview.h \
    interface_hydro_parameters_menu.h \
    interface_noise_layer.h \
    interface_noise_layers.h \
    interface_noise_parameters_menu.h \
    interface_splash_screen.h \
    interface_terrain_parameters_menu.h \
    noise_layer.h \
    terrain.h \
    world.h

FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
