#include "generation_menu.h"

generation_menu :: generation_menu(QWidget *parent) : QWidget(parent) {

    grid = new QGridLayout(this);

    persistence_slider = new QSlider(Qt :: Horizontal);
    persistence_slider -> setMaximum(10);
    persistence_slider -> setMinimum(2);
    persistence_slider -> setStyleSheet("QSlider { max-height: 24px; min-height: 24px; }"
                                "QSlider::add-page:qlineargradient { background: rgba(110, 110, 135, 1); }"
                                "QSlider::groove:horizontal { background: rgba(190, 190, 222, 1); height: 2px; }"
                                "QSlider::handle:horizontal { background: rgba(190, 190, 222, 1); border: 2px solid rgba(1, 1, 1, 0); height: 10px; width: 10px; margin: -6 -1px; border-radius: 7px; }");

    persistence_label = new QLabel(this);
    persistence_label  -> setText("Persistence");
    persistence_label  -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); margin-right: 6px; }");

    paramgen_button = new QPushButton("Generate With Parameters", this);
    paramgen_button -> setStyleSheet("QPushButton { height: 16px; min-height: 2em; background: rgba(190, 190, 222, 1); border: 0; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                     "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    randgen_button = new QPushButton("Generate Random", this);
    randgen_button -> setStyleSheet("QPushButton { height: 16px; min-height: 2em; background: rgba(190, 190, 222, 1); border: 0; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                    "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    connect(paramgen_button, SIGNAL(clicked()), parent, SLOT(load_scene()));
    connect(randgen_button, SIGNAL(clicked()), parent, SLOT(load_scene()));

    grid -> addWidget(persistence_label, 1, 0, 1, 1);
    grid -> addWidget(persistence_slider, 1, 1, 1, 1);

    grid -> addWidget(paramgen_button, 2, 0, 1, 1);
    grid -> addWidget(randgen_button, 2, 1, 1, 1);

}
