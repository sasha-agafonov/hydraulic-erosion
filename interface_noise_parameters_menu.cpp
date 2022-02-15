#include "interface_noise_parameters_menu.h"

noise_parameters_menu :: noise_parameters_menu(QWidget *parent) : QWidget(parent) {

    h_box = new QHBoxLayout(this);

    noise_layers_widget = new interface_noise_layers(this);

    heightmap_widget = new heightmap_preview(this);

    connect(this, SIGNAL(reload_heightmap_signal()), parent, SLOT(reload_heightmap()));

    h_box -> addWidget(noise_layers_widget);
    h_box -> addWidget(heightmap_widget);

}

void noise_parameters_menu :: reload_heightmap() {

    heightmap_widget -> reload_button -> setEnabled(false);
    emit reload_heightmap_signal();
}
