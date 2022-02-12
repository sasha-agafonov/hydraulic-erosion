#include "interface_noise_parameters_menu.h"

#define NOISE_LAYERS 10

noise_parameters_menu :: noise_parameters_menu(QWidget *parent) : QWidget(parent) {


    h_box = new QHBoxLayout(this);
    v_box = new QVBoxLayout(this);

    v_box -> setSpacing(15);

    heightmap_widget = new heightmap_preview(this);

    for (int i = 0; i < NOISE_LAYERS; i++) {
        noise_layers.push_back(new noise_layer(this, i + 1));
        v_box -> addWidget(noise_layers[i]);
    }

    noise_layers[0] -> activate_layer();

    h_box -> addLayout(v_box);
    h_box -> addWidget(heightmap_widget);

    update_new_layer_button();

}


void noise_parameters_menu :: update_new_layer_button() {

    // it is guaranteed that there is at most one layer not in the following order {active layers ... inactive layers}

    sort_layers();

    // if there is a single layer, forbid deleting it
    if (!noise_layers[1] -> active) noise_layers[0] -> delete_layer_button -> hide();
    else noise_layers[0] -> delete_layer_button -> show();

    for (int i = 1; i < NOISE_LAYERS; i++) {
        if (noise_layers[i - 1] -> active && !noise_layers[i] -> active) {
            noise_layers[i] -> display_button();
            for (int k = i + 1; k < NOISE_LAYERS; k++) noise_layers[k] -> deactivate_layer();
            return;
        }
    }
}


void noise_parameters_menu :: sort_layers() {

    for (int i = 0; i < NOISE_LAYERS; i++) {
        v_box -> removeWidget(noise_layers[i]);
        if (i < (NOISE_LAYERS - 1) && !noise_layers[i] -> active && noise_layers[i + 1] -> active) {
            noise_layers[NOISE_LAYERS] = noise_layers[i];
            noise_layers[i] = noise_layers[i + 1];
            noise_layers[i + 1] = noise_layers[NOISE_LAYERS];
        }
    }

    for (int i = 0; i < NOISE_LAYERS; i++) {
        noise_layers[i] -> layer_label -> setText(QString("Layer " + QString :: number(i + 1)));
        v_box -> addWidget(noise_layers[i]);
    }
}

