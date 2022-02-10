#include "interface_hydro_parameters_menu.h"

hydro_parameters_menu :: hydro_parameters_menu(QWidget *parent) : QWidget(parent) {

    box = new QHBoxLayout(this);
    grid = new QGridLayout(this);

    random_checkbox = new QCheckBox(this);

    water_amount = new QSlider(Qt :: Horizontal);
    water_amount -> setMaximum(10);
    water_amount -> setMinimum(1);

    cycles = new QSlider(Qt :: Horizontal);
    cycles -> setMaximum(10);
    cycles -> setMinimum(1);

    evap_rate = new QSlider(Qt :: Horizontal);
    evap_rate -> setMaximum(10);
    evap_rate -> setMinimum(1);

    erosion_rate = new QSlider(Qt :: Horizontal);
    erosion_rate -> setMaximum(10);
    erosion_rate -> setMinimum(1);

    carry_cap = new QSlider(Qt :: Horizontal);
    carry_cap -> setMaximum(10);
    carry_cap -> setMinimum(1);

    grid -> addWidget(new QLabel("Randomized Parameters", this), 0, 0, 1, 1);
    grid -> addWidget(random_checkbox, 0, 1, 1, 1);

    grid -> addWidget(new QLabel("  Cycles", this), 0, 2, 1, 1);
    grid -> addWidget(cycles, 0, 3, 1, 1);

    grid -> addWidget(new QLabel("Evaporation Rate", this), 1, 0, 1, 1);
    grid -> addWidget(evap_rate, 1, 1, 1, 1);

    grid -> addWidget(new QLabel("  Water Amount", this), 1, 2, 1, 1);
    grid -> addWidget(water_amount, 1, 3, 1, 1);

    grid -> addWidget(new QLabel("Erosion Rate", this), 2, 0, 1, 1);
    grid -> addWidget(erosion_rate, 2, 1, 1, 1);

    grid -> addWidget(new QLabel("  Carrying Capacity", this), 2, 2, 1, 1);
    grid -> addWidget(carry_cap, 2, 3, 1, 1);

    box -> addLayout(grid);
}
