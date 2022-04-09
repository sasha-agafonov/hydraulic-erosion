#include "interface_hydro_parameters_menu.h"
#include <iostream>

hydro_parameters_menu :: hydro_parameters_menu(QWidget *parent) : QWidget(parent) {

    h_box = new QHBoxLayout(this);
    v_box = new QVBoxLayout(this);
    v_box -> setSpacing(15);
    v_box -> setAlignment(Qt :: AlignTop);
    grid = new QGridLayout(this);

    hydro_parameters_label = new QLabel("Hydraulic Erosion Parameters", this);
    hydro_parameters_label -> setAlignment(Qt::AlignCenter);
    hydro_parameters_label -> setFixedHeight(30);
    hydro_parameters_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; }");

    random_checkbox = new QCheckBox(this);

    random_label = new QLabel("Randomized Appearance", this);
    random_label -> setFixedHeight(30);
    random_label -> setFixedWidth(160);
    random_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; padding-left: 8px; padding-right: 8px; }");
    random_label -> setAlignment(Qt::AlignCenter);

    cycles_slider = new QSlider(Qt :: Horizontal);
    cycles_slider -> setFixedHeight(30);
    cycles_slider -> setMaximum(200);
    cycles_slider -> setMinimum(10);

    cycles_spinbox = new QSpinBox(this);
    cycles_spinbox -> setFixedWidth(54);
    cycles_spinbox -> setRange(10, 200);
    cycles_spinbox -> setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    cycles_label = new QLabel("Number of Cycles", this);
    cycles_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; }");
    cycles_label -> setAlignment(Qt::AlignCenter);
    cycles_label -> setFixedHeight(30);

    water_amount_slider = new QSlider(Qt :: Horizontal);
    water_amount_slider -> setFixedHeight(30);
    water_amount_slider -> setMaximum(10);
    water_amount_slider -> setMinimum(1);

    water_amount_label = new QLabel("Water Amount", this);
    water_amount_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; }");
    water_amount_label -> setAlignment(Qt::AlignCenter);
    water_amount_label -> setFixedHeight(30);

    carrying_capacity_slider = new QSlider(Qt :: Horizontal);
    carrying_capacity_slider -> setFixedHeight(30);
    carrying_capacity_slider -> setMaximum(10);
    carrying_capacity_slider -> setMinimum(1);

    carrying_capacity_label = new QLabel("Carrying Capacity", this);
    carrying_capacity_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; }");
    carrying_capacity_label -> setAlignment(Qt::AlignCenter);
    carrying_capacity_label -> setFixedHeight(30);

    evaporation_rate_slider = new QSlider(Qt :: Horizontal);
    evaporation_rate_slider -> setFixedHeight(30);
    evaporation_rate_slider -> setRange(1, 100);
    evaporation_rate_slider -> setTickPosition(QSlider :: TicksBothSides);
    evaporation_rate_slider -> setTickInterval(20);
    evaporation_rate_slider -> setMinimumHeight(30);

    evaporation_rate_label = new QLabel("Evaporation Rate", this);
    evaporation_rate_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; }");
    evaporation_rate_label -> setAlignment(Qt::AlignCenter);
    evaporation_rate_label -> setFixedHeight(30);

    erosion_rate_slider = new QSlider(Qt :: Horizontal);
    erosion_rate_slider -> setFixedHeight(30);
    erosion_rate_slider -> setMaximum(10);
    erosion_rate_slider -> setMinimum(1);

    erosion_rate_label = new QLabel("Erosion Rate", this);
    erosion_rate_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; }");
    erosion_rate_label -> setAlignment(Qt::AlignCenter);
    erosion_rate_label -> setFixedHeight(30);

    deposition_rate_slider = new QSlider(Qt :: Horizontal);
    deposition_rate_slider -> setFixedHeight(30);
    deposition_rate_slider -> setMaximum(10);
    deposition_rate_slider -> setMinimum(1);

    deposition_rate_label = new QLabel("Deposition Rate", this);
    deposition_rate_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; }");
    deposition_rate_label -> setAlignment(Qt::AlignCenter);
    deposition_rate_label -> setFixedHeight(30);

    timer = new QTimer;

    // sorry
    connect(random_checkbox, SIGNAL(stateChanged(int)), this, SLOT(erosion_parameters_changed()));

    connect(cycles_slider, SIGNAL(valueChanged(int)), this, SLOT(erosion_parameters_changed()));
    connect(cycles_slider, SIGNAL(valueChanged(int)), cycles_spinbox, SLOT(setValue(int)));
    connect(cycles_spinbox, SIGNAL(valueChanged(int)), cycles_slider, SLOT(setValue(int)));

    connect(water_amount_slider, SIGNAL(valueChanged(int)), this, SLOT(erosion_parameters_changed()));
    connect(carrying_capacity_slider, SIGNAL(valueChanged(int)), this, SLOT(erosion_parameters_changed()));
    connect(evaporation_rate_slider, SIGNAL(valueChanged(int)), this, SLOT(erosion_parameters_changed()));
    connect(erosion_rate_slider, SIGNAL(valueChanged(int)), this, SLOT(erosion_parameters_changed()));
    connect(deposition_rate_slider, SIGNAL(valueChanged(int)), this, SLOT(erosion_parameters_changed()));

    connect(timer, SIGNAL(timeout()), this, SLOT(reload_heighmap()));



    hydraulic_erosion = new hydro();

//    hydraulic_erosion -> erode();

    hydraulic_erosion2 = new hydro2();

    hydraulic_erosion3 = new hydro3(this);

//    hydraulic_erosion2 -> load_heightmap();
//    hydraulic_erosion2 -> create_bounded_heightmap();
//    hydraulic_erosion2 -> create_bounded_watermap();
////    hydraulic_erosion2 -> create_sediment_map();
//    hydraulic_erosion2 -> output_heightmap();

    eroded_heightmap = new eroded_heightmap_preview(this);

    grid -> addWidget(cycles_label, 0, 0, 1, 1);
    grid -> addWidget(cycles_slider, 0, 1, 1, 1);
    grid -> addWidget(cycles_spinbox, 0, 2, 1, 1);

    grid -> addWidget(water_amount_label, 1, 0, 1, 1);
    grid -> addWidget(water_amount_slider, 1, 1, 1, 1);

    grid -> addWidget(carrying_capacity_label, 2, 0, 1, 1);
    grid -> addWidget(carrying_capacity_slider, 2, 1, 1, 1);

    grid -> addWidget(erosion_rate_label, 3, 0, 1, 1);
    grid -> addWidget(erosion_rate_slider, 3, 1, 1, 1);

    grid -> addWidget(deposition_rate_label, 4, 0, 1, 1);
    grid -> addWidget(deposition_rate_slider, 4, 1, 1, 1);

    grid -> addWidget(evaporation_rate_label, 5, 0, 1, 1);
    grid -> addWidget(evaporation_rate_slider, 5, 1, 1, 1);

    grid -> addWidget(random_label, 6, 0, 1, 1);
    grid -> addWidget(random_checkbox, 6, 1, 1, 1);

    v_box -> addWidget(hydro_parameters_label);
    v_box -> addLayout(grid);
    h_box -> addLayout(v_box);
    h_box -> addWidget(eroded_heightmap);
}

void hydro_parameters_menu :: original_heightmap_invalid() {

    eroded_heightmap -> reload_button -> setEnabled(false);
    eroded_heightmap -> reload_button -> setText("Please reload the original heightmap first");
    eroded_heightmap -> reload_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                       "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
}

void hydro_parameters_menu :: original_heightmap_changed() {

    eroded_heightmap -> reload_button -> setEnabled(true);
    eroded_heightmap -> reload_button -> setText("Original heightmap changed, press to erode again");
    eroded_heightmap -> reload_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                       "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
}

void hydro_parameters_menu :: erosion_parameters_changed() {

    if (!eroded_heightmap -> reload_button -> isEnabled()) eroded_heightmap -> reload_button -> setEnabled(true);

    eroded_heightmap -> reload_button -> setText("Erosion parameters changed, press to erode again");
    eroded_heightmap -> reload_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                       "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
}

void hydro_parameters_menu :: erode_heightmap() {


//    hydraulic_erosion2 -> load_heightmap();
//    hydraulic_erosion2 -> create_bounded_heightmap();
//    hydraulic_erosion2 -> create_bounded_watermap();
//    hydraulic_erosion2 -> create_sediment_map();
////    hydraulic_erosion2 -> distribute_water(120000);
//    hydraulic_erosion2 -> erode(cycles_slider -> value());
//    hydraulic_erosion2 -> drop();
//    hydraulic_erosion2 -> output_heightmap();

    hydraulic_erosion3 -> initialize_maps();

//    hydraulic_erosion3 -> check();
    hydraulic_erosion3 -> erode(1000);

    eroded_heightmap -> reload_heightmap();

}


void hydro_parameters_menu :: reload_heightmap() { eroded_heightmap -> refresh_heightmap(); }
