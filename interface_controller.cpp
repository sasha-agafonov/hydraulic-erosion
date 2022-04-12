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

    in_menu = true;

    splash = new splash_screen(this);

    QGLFormat format;
    format.setSampleBuffers(true);
    format.setSamples(4);

    scene = new world(this);
    scene -> setFormat(format);

    gen_menu = new generation_menu(this);
    ldg_menu = new loading_menu(this);

    box = new QVBoxLayout(this);

    box -> setContentsMargins(0, 0, 0, 0);

    // ~ 200 fps cap
    timer = new QTimer;
    timer -> start(5);
    timer2 = new QTimer;
    timer2 -> start(1000);

    connect(timer, SIGNAL(timeout()), this->scene, SLOT(update_scene()));
    connect(timer2, SIGNAL(timeout()), this->scene, SLOT(resetFPS()));

    box -> addWidget(scene);
    box -> addWidget(gen_menu);
    box -> addWidget(ldg_menu);
    box -> addWidget(splash);

    scene -> hide();
    ldg_menu -> hide();
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


void interface_controller :: scene_ready() {
    ldg_menu -> show();
}


void interface_controller:: reload_scene() {


    gen_menu -> hide();
    scene -> show();

}


void interface_controller :: exit_scene() {

    scene -> hide();
    gen_menu -> show();

}


void interface_controller :: toggle_scene_menu() {
     scene -> hide();

     gen_menu -> hide();
     ldg_menu -> hide();
}



interface_controller :: ~interface_controller() {
    delete box;
    delete grid;
    delete scene;
    delete timer;
    delete button_box;
}


