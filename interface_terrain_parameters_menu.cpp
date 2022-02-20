#include "interface_terrain_parameters_menu.h"

terrain_parameters_menu :: terrain_parameters_menu(QWidget* parent) : QWidget(parent) {

    this -> setSizePolicy(QSizePolicy :: Expanding, QSizePolicy :: Fixed);

    v_box = new QVBoxLayout(this);

    h_box_1 = new QHBoxLayout(this);
    h_box_1 -> setSpacing(15);
    h_box_1 -> setContentsMargins(10, 20, 0, 0);
    h_box_1 -> setAlignment(Qt :: AlignBottom);

    terrain_size_label = new QLabel("Terrain Size", this);
    terrain_size_label -> setStyleSheet("QLabel { background-color: rgba(1,1,1, 0); color: rgba(190, 190, 222, 1); } ");
    terrain_size_label -> setFixedWidth(65);
    terrain_size_label -> setFixedHeight(30);

    width_x_spinbox = new QSpinBox(this);
    width_x_spinbox -> setFixedHeight(25);
    width_x_spinbox -> setFixedWidth(60);
    width_x_spinbox -> setMinimum(1);
    width_x_spinbox -> setMaximum(1000);
    width_x_spinbox -> setValue(100);

    width_y_spinbox = new QSpinBox(this);
    width_y_spinbox -> setFixedHeight(25);
    width_y_spinbox -> setFixedWidth(60);
    width_y_spinbox -> setMinimum(1);
    width_y_spinbox -> setMaximum(1000);
    width_y_spinbox -> setValue(100);

    connect(width_x_spinbox, SIGNAL(valueChanged(int)), this, SLOT(equalize_size_y()));
    connect(width_y_spinbox, SIGNAL(valueChanged(int)), this, SLOT(equalize_size_x()));

    h_box_1 -> addWidget(terrain_size_label);
    h_box_1 -> addWidget(width_x_spinbox);
    h_box_1 -> addWidget(width_y_spinbox);



    h_box_2 = new QHBoxLayout(this);
    h_box_2 -> setSpacing(15);
    h_box_2 -> setContentsMargins(10, 10, 0, 0);

    gradient_seed_label = new QLabel("Random Gradients", this);
    gradient_seed_label -> setFixedHeight(30);
    gradient_seed_label -> setFixedWidth(100);
    gradient_seed_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 0); height: 30px; margin: 0; }");

    gradient_seed_checkbox = new QCheckBox(this);

    h_box_2 -> addWidget(gradient_seed_label);
    h_box_2 -> addWidget(gradient_seed_checkbox);


    h_box_3 = new QHBoxLayout(this);
    h_box_3 -> setSpacing(15);
    h_box_3 -> setContentsMargins(10, 10, 0, 0);

    materials_label = new QLabel("T2", this);
    materials_label -> setFixedHeight(30);
    materials_label -> setFixedWidth(100);
    materials_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 0); height: 30px; margin: 0; }");

    materials_checkbox = new QCheckBox(this);

    h_box_3 -> addWidget(materials_label);
    h_box_3 -> addWidget(materials_checkbox);

    v_box -> addLayout(h_box_1);
    v_box -> addLayout(h_box_2);
    v_box -> addLayout(h_box_3);

}

void terrain_parameters_menu :: equalize_size_x() { width_x_spinbox -> setValue(width_y_spinbox -> value()); }

void terrain_parameters_menu :: equalize_size_y() { width_y_spinbox -> setValue(width_x_spinbox -> value()); }
