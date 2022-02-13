#include "interface_terrain_parameters_menu.h"

terrain_parameters_menu :: terrain_parameters_menu(QWidget* parent) : QWidget(parent) {

    this -> setSizePolicy(QSizePolicy :: Expanding, QSizePolicy :: Fixed);

    box = new QHBoxLayout(this);
    box -> setSpacing(15);
    box -> setContentsMargins(20, 20, 0, 0);
    box -> setAlignment(Qt :: AlignBottom);

    terrain_size_label = new QLabel("Terrain Size", this);
    terrain_size_label -> setStyleSheet("QLabel { background-color: rgba(1,1,1, 0); color: rgba(190, 190, 222, 1); } ");
    terrain_size_label -> setFixedWidth(65);
    terrain_size_label -> setFixedHeight(30);

    width_x_spinbox = new QSpinBox(this);
    width_x_spinbox -> setFixedHeight(25);
    width_x_spinbox -> setFixedWidth(60);
    width_x_spinbox -> setMinimum(1);
    width_x_spinbox -> setMaximum(1000);
    width_x_spinbox -> setValue(400);

    width_y_spinbox = new QSpinBox(this);
    width_y_spinbox -> setFixedHeight(25);
    width_y_spinbox -> setFixedWidth(60);
    width_y_spinbox -> setMinimum(1);
    width_y_spinbox -> setMaximum(1000);
    width_y_spinbox -> setValue(400);

    connect(width_x_spinbox, SIGNAL(valueChanged(int)), this, SLOT(equalize_size_y()));
    connect(width_y_spinbox, SIGNAL(valueChanged(int)), this, SLOT(equalize_size_x()));

    box -> addWidget(terrain_size_label);
    box -> addWidget(width_x_spinbox);
    box -> addWidget(width_y_spinbox);

}

void terrain_parameters_menu :: equalize_size_x() { width_x_spinbox -> setValue(width_y_spinbox -> value()); }

void terrain_parameters_menu :: equalize_size_y() { width_y_spinbox -> setValue(width_x_spinbox -> value()); }
