#include "interface_controller.h"
#include "world.h"
#include <iostream>
#include <QShortcut>
#include <QCoreApplication>
#include <QGLFormat>
#include <QLineEdit>
#include <QListView>
#include <QThread>
#include <QPixmap>
#include <QSplashScreen>

interface_controller :: interface_controller(QWidget* parent) : QWidget(parent) {

    splash = new splash_screen(this);

    QGLFormat format;
    format.setSampleBuffers(true);
    format.setSamples(4);

    scene = new world(this);
    scene -> setFormat(format);

    gen_menu = new generation_menu(this);

    box = new QVBoxLayout(this);
    box -> setContentsMargins(0, 0, 0, 0);

    timer = new QTimer;
    timer -> start(16);
    timer2 = new QTimer;
    timer2 -> start(1000);

    connect(timer, SIGNAL(timeout()), this->scene, SLOT(update_scene()));
    connect(timer2, SIGNAL(timeout()), this->scene, SLOT(resetFPS()));

    box -> addWidget(scene);
    box -> addWidget(gen_menu);
    box -> addWidget(splash);

    scene -> hide();
    gen_menu -> show();
    splash -> hide();

    setLayout(box);

}


void interface_controller :: load_scene() {

    gen_menu -> hide();
    splash -> show();
    scene -> initializeGL();
    splash -> finish(scene);
    scene -> show();

}


void interface_controller :: load_eroded() {

    gen_menu -> hide();
    scene -> bad_terrain -> eroded = true;
    scene -> bad_terrain -> dynamic = false;
    scene -> bad_terrain -> load_terrain();

    scene -> camera -> position_x = -scene -> bad_terrain -> max;
    scene -> camera -> position_y = -scene -> bad_terrain -> max;
    scene -> camera -> position_z = scene -> bad_terrain -> max * 3;

    scene -> cursor_x = -135;
    scene -> cursor_y = 110;
    scene -> camera -> set_angles(-135, 110);

    splash -> show();
    splash -> finish(scene);
    scene -> show();
    scene -> grabMouse();
    scene -> grabKeyboard();

}


void interface_controller :: load_uneroded() {

    gen_menu -> hide();
    splash -> show();
    scene -> bad_terrain -> eroded = false;
    scene -> bad_terrain -> dynamic = false;
    scene -> bad_terrain -> load_terrain();

    scene -> camera -> position_x = -scene -> bad_terrain -> max;
    scene -> camera -> position_y = -scene -> bad_terrain -> max;
    scene -> camera -> position_z = scene -> bad_terrain -> max * 3;

    scene -> cursor_x = -135;
    scene -> cursor_y = 110;
    scene -> camera -> set_angles(-135, 110);

    splash -> finish(scene);
    scene -> show();
    scene -> grabMouse();
    scene -> grabKeyboard();
}



void interface_controller :: load_and_erode() {

    gen_menu -> hide();
    splash -> show();
    scene -> bad_terrain -> eroded = false;
    scene -> bad_terrain -> dynamic = true;
    scene -> bad_terrain -> loaded = false;
    scene -> bad_terrain -> load_terrain();

    scene -> camera -> position_x = -scene -> bad_terrain -> max;
    scene -> camera -> position_y = -scene -> bad_terrain -> max;
    scene -> camera -> position_z = scene -> bad_terrain -> max * 3;

    scene -> cursor_x = -135;
    scene -> cursor_y = 110;
    scene -> camera -> set_angles(-135, 110);

    scene -> bad_terrain -> current_cycle = 0;
    scene -> bad_terrain -> cycles = gen_menu -> hydro_parameters -> cycles_spinbox -> value();
    scene -> bad_terrain -> hydraulic_erosion -> set_parameters(gen_menu -> hydro_parameters -> water_spinbox -> value(),
                                                                gen_menu -> hydro_parameters -> carry_spinbox -> value(),
                                                                gen_menu -> hydro_parameters -> erosion_spinbox -> value(),
                                                                gen_menu -> hydro_parameters -> deposition_spinbox -> value(),
                                                                gen_menu -> hydro_parameters -> evaporation_spinbox -> value(),
                                                                gen_menu -> hydro_parameters -> post_evaporation_spinbox -> value(),
                                                                gen_menu -> hydro_parameters -> random_checkbox -> isChecked());
    splash -> finish(scene);
    scene -> show();
    scene -> grabMouse();
    scene -> grabKeyboard();

}


void interface_controller :: exit_scene() {

    scene -> hide();
    gen_menu -> show();

}


interface_controller :: ~interface_controller() {

    delete box;
    delete scene;
    delete timer;

}
