#include "interface_terrain_parameters_menu.h"

terrain_parameters_menu :: terrain_parameters_menu(QWidget* parent) : QWidget(parent) {

    box = new QHBoxLayout(this);
    box -> setAlignment(Qt :: AlignLeft | Qt :: AlignTop);

    grid = new QGridLayout(this);
    grid -> setSpacing(15);

    terrain_size_label = new QLabel("Terrain Size", this);
    terrain_size_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; padding-left: 8px; padding-right: 8px; }");
    terrain_size_label -> setFixedHeight(30);
    terrain_size_label -> setFixedWidth(160);
    terrain_size_label -> setAlignment(Qt::AlignCenter);

    width_x_spinbox = new QSpinBox(this);
    width_x_spinbox -> setFixedHeight(28);
    width_x_spinbox -> setFixedWidth(60);
    width_x_spinbox -> setMinimum(1);
    width_x_spinbox -> setMaximum(1000);
    width_x_spinbox -> setValue(500);
    width_x_spinbox -> setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    width_y_spinbox = new QSpinBox(this);
    width_y_spinbox -> setFixedHeight(28);
    width_y_spinbox -> setFixedWidth(60);
    width_y_spinbox -> setMinimum(1);
    width_y_spinbox -> setMaximum(1000);
    width_y_spinbox -> setValue(500);
    width_y_spinbox -> setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    gradient_seed_label = new QLabel("Random Seed", this);
    gradient_seed_label -> setFixedHeight(30);
    gradient_seed_label -> setAlignment(Qt::AlignCenter);
    gradient_seed_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; padding-left: 8px; padding-right: 8px; }");

    gradient_seed_checkbox = new QCheckBox(this);

    // ensures terrain is a square
    connect(width_x_spinbox, SIGNAL(valueChanged(int)), this, SLOT(equalize_size_y()));
    connect(width_y_spinbox, SIGNAL(valueChanged(int)), this, SLOT(equalize_size_x()));

    // allows to reload the heightmap when changing parameters
    connect(width_x_spinbox, SIGNAL(valueChanged(int)), parent, SLOT(terrain_changed()));
    connect(width_y_spinbox, SIGNAL(valueChanged(int)), parent, SLOT(terrain_changed()));
    connect(gradient_seed_checkbox, SIGNAL(stateChanged(int)), parent, SLOT(terrain_changed()));

    grid -> addWidget(terrain_size_label, 0, 0, 1, 1);
    grid -> addWidget(width_x_spinbox, 0, 1, 1, 1);
    grid -> addWidget(width_y_spinbox, 0, 2, 1, 1);
    grid -> addWidget(gradient_seed_label, 1, 0, 1, 1);
    grid -> addWidget(gradient_seed_checkbox, 1, 1, 1, 1);

    box -> addLayout(grid);
    box -> setSizeConstraint(QLayout :: SetMinimumSize);

}

void terrain_parameters_menu :: equalize_size_x() { width_x_spinbox -> setValue(width_y_spinbox -> value()); }

void terrain_parameters_menu :: equalize_size_y() { width_y_spinbox -> setValue(width_x_spinbox -> value()); }
