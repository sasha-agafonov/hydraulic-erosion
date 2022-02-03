#include "interface.h"
#include "world.h"
#include <iostream>
#include <QShortcut>
#include <QGLFormat>

interface :: interface(QWidget *parent) : QWidget(parent) {

    in_menu = true;

    menuBar = new QMenuBar(this);
    fileMenu = menuBar->addMenu("&Black Noise");
    actionQuit = new QAction("&Quit", this);
    fileMenu->addAction(actionQuit);

    QGLFormat format;
    format.setSampleBuffers(true);
    format.setSamples(4);
    scene = new world(format, this);

//    scene -> hide();

    //grid = new grid_layout(this);

    box = new QVBoxLayout(this);

   // box->setSpacing(0);


    box->setContentsMargins(0, 0, 0, 0);
    button_box = new QBoxLayout(QBoxLayout :: LeftToRight, this);
    //grid = new QGridLayout();

    // ~ 200 fps cap
    timer = new QTimer;
    timer -> start(5);
    timer2 = new QTimer;
    timer2 -> start(1000);


//    persistence_slider = new QSlider(Qt :: Horizontal);
//    persistence_slider -> setMaximum(10);
//    persistence_slider -> setMinimum(2);
//    persistence_slider -> setStyleSheet("QSlider { max-height: 24px; min-height: 24px; }"
//                                "QSlider::add-page:qlineargradient { background: rgba(110, 110, 135, 1); }"
//                                "QSlider::groove:horizontal { background: rgba(190, 190, 222, 1); height: 2px; }"
//                                "QSlider::handle:horizontal { background: rgba(190, 190, 222, 1); border: 2px solid rgba(1, 1, 1, 0); height: 10px; width: 10px; margin: -6 -1px; border-radius: 7px; }");

//    persistence_label = new QLabel(this);
//    persistence_label  -> setText("Persistence");
//    persistence_label  -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); margin-right: 6px; }");

    paramgenerate_button = new QPushButton("Generate With Parameters", this);
    paramgenerate_button-> setStyleSheet("QPushButton { height: 16px; min-height: 2em; background: rgba(190, 190, 222, 1); border: 0; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    randgenerate_button = new QPushButton("Generate Random", this);
    randgenerate_button -> setStyleSheet("QPushButton { height: 16px; min-height: 2em; background: rgba(190, 190, 222, 1); border: 0; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    connect(paramgenerate_button, SIGNAL(clicked()), this, SLOT(switch_window()));
    connect(randgenerate_button, SIGNAL(clicked()), this, SLOT(switch_window()));

    connect(timer, SIGNAL(timeout()), this->scene, SLOT(update_scene()));
    connect(timer2, SIGNAL(timeout()), this->scene, SLOT(resetFPS()));
    //connect(this, SIGNAL(cu()), this->scene, SLOT(cameraUpdate(2,0,0)));

//    button_box -> addWidget(paramgenerate_button);
//    button_box -> addWidget(randgenerate_button);

//    grid -> addWidget(persistence_label, 1, 0, 1, 1);
//    grid -> addWidget(persistence_slider, 1, 1, 1, 1);

   // box -> addLayout(button_box);
    //scene-> setStyleSheet("border: 0");
    box -> addWidget(randgenerate_button);
    box -> addWidget(paramgenerate_button);
    box -> addWidget(scene);


    //box->setContentMargin(0, 0, 0, 0);
    scene->hide();
//    box -> addLayout(grid -> grid);

}

interface :: ~interface() {

    delete box;
    delete grid;
    delete scene;
    delete timer;
    delete button_box;
}

void interface :: switch_window() {
    if (in_menu) {
        in_menu = false;
        world_view();
    } else {
        in_menu = true;
        main_menu();
    }
}

void interface :: main_menu() {
    scene -> hide();
    randgenerate_button -> show();
    paramgenerate_button -> show();
}


void interface :: world_view() {
    randgenerate_button -> hide();
    paramgenerate_button -> hide();
    scene -> show();
        scene -> setFocus();
}

//void interface :: keyPressEvent(QKeyEvent* event) {
//    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_A),this->scene,SLOT(cameraUpdate(2, 2, 2)));

//    if (event -> key() == Qt :: Key_Escape && !in_menu) this -> switch_window();
//    if (event -> key() == Qt :: Key_W && !in_menu) emit this -> cu();
//    if (event -> key() == Qt :: Key_A && !in_menu) emit this -> cu();
//    if (event -> key() == Qt :: Key_S && !in_menu) emit this -> cu();
//    if (event -> key() == Qt :: Key_D && !in_menu) emit this -> cu();
//}



