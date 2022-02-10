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

//    menuBar = new QMenuBar(this);

//    fileMenu = menuBar->addMenu("&Black Noise");

//    actionQuit = new QAction("&Quit", this);

//    fileMenu->addAction(actionQuit);

    splash = new splash_screen(this);
    QGLFormat format;
    format.setSampleBuffers(true);
    format.setSamples(4);

    scene = new world(format, this, splash);

    //QSplashScreen* splash = new QSplashScreen(pixmap);

    sc_menu = new scene_menu(this);
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
    box -> addWidget(sc_menu);
    box -> addWidget(gen_menu);
    box -> addWidget(ldg_menu);
    box -> addWidget(splash);

    scene -> hide();
    sc_menu -> hide();
    ldg_menu -> hide();
    gen_menu -> show();
    splash -> hide();

    setLayout(box);

}


void interface_controller :: load_scene() {
    gen_menu -> hide();

    splash -> show();



//    splash->showMessage("Generation...");
    QCoreApplication :: processEvents();


    //scene -> initializeGL();
    splash -> finish(scene);
    scene -> show();

//    ldg_menu -> hide();
}


void interface_controller :: scene_ready() {
//    scene -> show();
    ldg_menu -> show();
}


void interface_controller:: reload_scene() {

    sc_menu -> hide();
    gen_menu -> hide();

//       ldg_menu -> show();
//        for (int i = 0 ; i < 1000000000; i++) {}
//          ldg_menu -> hide();
//             gen_menu -> show();

    scene -> show();

}


void interface_controller :: exit_scene() {
    scene -> hide();
    sc_menu -> hide();
    gen_menu -> show();
    ldg_menu -> hide();
}


void interface_controller :: toggle_scene_menu() {
     scene -> hide();
     sc_menu -> show();
     gen_menu -> hide();
     ldg_menu -> hide();
}


void interface_controller :: main_menu() {
//    randgenerate_button -> hide();
//    antialiasing_combo -> hide();
//    scene -> hide();

//    /paramgenerate_button -> show();
}


void interface_controller :: world_view() {
    delete scene;
    sc_menu -> show();

//     stack -> widget(0) -> hide();
//     stack -> widget(1) -> show();
     //stack -> widget(2) -> hide();
//    randgenerate_button -> hide();
    //paramgenerate_button -> hide();


//    scene -> show();
//    scene -> setFocus();
}

//void interface :: keyPressEvent(QKeyEvent* event) {
//    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_A),this->scene,SLOT(cameraUpdate(2, 2, 2)));

//    if (event -> key() == Qt :: Key_Escape && !in_menu) this -> switch_window();
//    if (event -> key() == Qt :: Key_W && !in_menu) emit this -> cu();
//    if (event -> key() == Qt :: Key_A && !in_menu) emit this -> cu();
//    if (event -> key() == Qt :: Key_S && !in_menu) emit this -> cu();
//    if (event -> key() == Qt :: Key_D && !in_menu) emit this -> cu();
//}

interface_controller :: ~interface_controller() {
    delete box;
    delete grid;
    delete scene;
    delete timer;
    delete button_box;
}


