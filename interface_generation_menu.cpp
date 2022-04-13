#include "interface_generation_menu.h"

generation_menu :: generation_menu(QWidget *parent) : QWidget(parent) {

    v_box = new QVBoxLayout(this);
    h_box = new QHBoxLayout(this);

    terrain_parameters = new terrain_parameters_menu(this);

    noise_parameters = new noise_parameters_menu(this,
                                                 terrain_parameters -> width_x_spinbox -> value(),
                                                 terrain_parameters -> width_y_spinbox -> value(),
                                                 terrain_parameters -> gradient_seed_checkbox -> isChecked());

    hydro_parameters = new hydro_parameters_menu(this);

    terrain_parameters -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    noise_parameters -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    hydro_parameters -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);


    build_eroded_button = new QPushButton("BUILD ERODED TERRAIN", this);
    build_eroded_button -> setFixedHeight(30);
    build_eroded_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                  "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    build_uneroded_button = new QPushButton("BUILD UNERODED TERRAIN", this);
    build_uneroded_button -> setFixedHeight(30);
    build_uneroded_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                          "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    build_and_erode_button = new QPushButton("BUILD AND ERODE TERRAIN", this);
    build_and_erode_button -> setFixedHeight(30);
    build_and_erode_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                          "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");


    connect(build_eroded_button, SIGNAL(clicked()), parent, SLOT(load_eroded()));
    connect(build_uneroded_button, SIGNAL(clicked()), parent, SLOT(load_uneroded()));
    connect(build_and_erode_button, SIGNAL(clicked()), parent, SLOT(load_and_erode()));
    connect(this, SIGNAL(invalidate_heightmap_signal()), noise_parameters, SLOT(invalidate_heightmap()));

    h_box -> setContentsMargins(11, 11, 11, 0);
    h_box -> addWidget(build_eroded_button);
    h_box -> addWidget(build_uneroded_button);
    h_box -> addWidget(build_and_erode_button);

    v_box -> addWidget(terrain_parameters);
    v_box -> addWidget(noise_parameters);
    v_box -> addWidget(hydro_parameters);

    v_box -> addLayout(h_box);

    noisy = new noise();
    water = new hydro();

}


void generation_menu :: reload_heightmap() {

    noise_parameters -> noise_layers_widget -> build_layers(terrain_parameters -> width_x_spinbox -> value(),
                                                            terrain_parameters -> width_y_spinbox -> value(),
                                                            terrain_parameters -> gradient_seed_checkbox -> isChecked());

    if (terrain_parameters -> gradient_seed_checkbox -> isChecked()) noise_parameters -> heightmap_widget -> reload_button -> setText("Reload with a different seed");

    else {

        noise_parameters -> heightmap_widget -> reload_button -> setEnabled(false);
        noise_parameters -> heightmap_widget -> reload_button -> setText("Currently up-to-date");
        noise_parameters -> heightmap_widget -> reload_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                                               "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
    }

    hydro_parameters -> original_heightmap_changed();
}


void generation_menu :: terrain_changed() {

    build_eroded_button -> setEnabled(false);
    build_eroded_button -> setText("CANNOT BUILD: Eroded heightmap needs to be up-to-date");
    build_eroded_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                       "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
    build_uneroded_button -> setEnabled(false);
    build_uneroded_button -> setText("CANNOT BUILD: Noise heightmap needs to be up-to-date");
    build_uneroded_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                       "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
    build_and_erode_button -> setEnabled(false);
    build_and_erode_button -> setText("CANNOT BUILD: Noise heightmap needs to be up-to-date");
    build_and_erode_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                       "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
    emit invalidate_heightmap_signal();

}


void generation_menu :: invalidate_eroded_heightmap() {

    build_eroded_button -> setEnabled(false);
    build_eroded_button -> setText("CANNOT BUILD: Eroded heightmap needs to be up-to-date");
    build_eroded_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                       "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
    build_uneroded_button -> setEnabled(false);
    build_uneroded_button -> setText("CANNOT BUILD: Noise heightmap needs to be up-to-date");
    build_uneroded_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                       "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
    build_and_erode_button -> setEnabled(false);
    build_and_erode_button -> setText("CANNOT BUILD: Noise heightmap needs to be up-to-date");
    build_and_erode_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                                       "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    hydro_parameters -> original_heightmap_invalid();

}


void generation_menu :: eroded_heightmap_valid() {

    build_eroded_button -> setEnabled(true);
    build_eroded_button -> setText("BUILD ERODED TERRAIN");
    build_eroded_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                  "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
}


void generation_menu :: heightmap_valid() {

    build_uneroded_button -> setEnabled(true);
    build_uneroded_button -> setText("BUILD UNERODED TERRAIN");
    build_uneroded_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                          "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    build_and_erode_button -> setEnabled(true);
    build_and_erode_button -> setText("BUILD AND ERODE TERRAIN");
    build_and_erode_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                          "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
}
