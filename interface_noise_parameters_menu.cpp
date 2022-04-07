#include "interface_noise_parameters_menu.h"

noise_parameters_menu :: noise_parameters_menu(QWidget *parent, int wx, int wy, bool random) : QWidget(parent) {

    h_box = new QHBoxLayout(this);
    noise_layers_widget = new interface_noise_layers(this, wx, wy, random);

    // chain
    connect(this, SIGNAL(reload_heightmap_signal()), parent, SLOT(reload_heightmap()));
    connect(this, SIGNAL(invalidate_eroded_heightmap_signal()), parent, SLOT(invalidate_eroded_heightmap()));

    // read and display in the interface
    heightmap_widget = new heightmap_preview(this);

    // noise layers
    h_box -> addWidget(noise_layers_widget);

    // heightmap
    h_box -> addWidget(heightmap_widget);

}

void noise_parameters_menu :: invalidate_heightmap() {

    emit invalidate_eroded_heightmap_signal();

    if (!heightmap_widget -> reload_button -> isEnabled()) heightmap_widget -> reload_button -> setEnabled(true);
    heightmap_widget -> reload_button -> setText("Parameters changed, press to reload heightmap");
    heightmap_widget -> reload_button -> setStyleSheet("QPushButton { height: 30px; background-color: rgba(190, 190, 222, 1);border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                   "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
}

void noise_parameters_menu :: reload_heightmap() { emit reload_heightmap_signal(); }
