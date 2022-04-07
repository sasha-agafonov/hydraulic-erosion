#include <fstream>
#include <iostream>
#include <cmath>
#include "interface_noise_layers.h"

#define NOISE_LAYERS 10
#define PGM_16_BIT 65535


interface_noise_layers :: interface_noise_layers(QWidget* parent, int wx, int wy, bool random) : QWidget(parent) {

    box = new QVBoxLayout(this);
    box -> setContentsMargins(0, 0, 0, 0);
    box -> setSpacing(6);
    box -> setAlignment(Qt :: AlignTop);

    noise_layers_label = new QLabel("Noise Layers", this);
    noise_layers_label -> setAlignment(Qt::AlignCenter);
    noise_layers_label -> setFixedHeight(30);
    noise_layers_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; }");

    box -> addWidget(noise_layers_label);

    for (int i = 0; i < NOISE_LAYERS; i++) {
        layers_vector.push_back(new interface_noise_layer(this, i + 1));
        box -> addWidget(layers_vector[i]);
    }

    alpha_map = new noise_layer;

    layers_vector[0] -> activate_layer();
    update_new_layer_button();

    layers_vector[1] -> activate_layer();
    update_new_layer_button();
    layers_vector[1] -> frequency_spinbox -> setValue(3);

    layers_vector[2] -> activate_layer();
    update_new_layer_button();
    layers_vector[2] -> frequency_spinbox -> setValue(5);

    layers_vector[3] -> activate_layer();
    update_new_layer_button();
    layers_vector[3] -> frequency_spinbox -> setValue(10);

    layers_vector[4] -> activate_layer();
    update_new_layer_button();
    layers_vector[4] -> frequency_spinbox -> setValue(60);
    layers_vector[4] -> amplitude_spinbox -> setValue(4);

    connect(this, SIGNAL(invalidate_heightmap_signal()), parent, SLOT(invalidate_heightmap()));

    build_layers(wx, wy, random);

}


// construct a heightmap from the current configuration of layers
void interface_noise_layers :: build_layers(int width, int height, bool random) {

    std :: vector < std :: vector <int> > heightmap(height, std :: vector <int> (width, 0));

    for (int i = 0; i < NOISE_LAYERS; i++) {
        if (layers_vector[i] -> active) {

            layers_vector[i] -> noise -> create_layer(width, height,
            layers_vector[i] -> frequency_spinbox -> value() + 1, layers_vector[i] -> frequency_spinbox -> value() + 1,
            layers_vector[i] -> amplitude_spinbox -> value(), random);

            for (int k = 0; k < height; k++) {
                for (int x = 0; x < width; x++) heightmap[k][x] += (layers_vector[i] -> noise -> heightmap[k][x] * layers_vector[i] -> transparency_spinbox -> value());
            }
        }
    }

    float max = PGM_16_BIT;
    float min = 0;

    for (int i = 0; i < height; i++) {
        for (int k = 0; k < height; k++) {
            if (max < heightmap[i][k]) max = heightmap[i][k];
            if (min > heightmap[i][k]) min = heightmap[i][k];
        }
    }

    float compression_factor = (float) PGM_16_BIT / (max - min);

    std :: cout << "max: " << max << "\n";
    std :: cout << "min: " << min << "\n";
    std :: cout << "cof: " << compression_factor << "\n";


    for (int i = 0; i < height; i++) {
        for (int k = 0; k < width; k++ ) {
            if (min < 0) heightmap[i][k] += (-min);
            heightmap[i][k] *= compression_factor;
            heightmap[i][k] = floor(heightmap[i][k]);
        }
    }

    std :: ofstream happy_file;

    // heightmap for erosion
    happy_file.open("../terrain/heightmap.pgm");
    happy_file << "P2\n";
    happy_file << width << ' ' << height << '\n';
    happy_file << "65535\n";

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << static_cast <int> (heightmap[i][k]) << '\n';
            else happy_file << static_cast <int> (heightmap[i][k]) << ' ';
        }
    }

    happy_file.close();

    // heightmap for preview
    happy_file.open("../terrain/heightmap_preview.ppm");
    happy_file << "P3\n";
    happy_file << width << ' ' << height << '\n';
    happy_file << "65535\n";

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {

            // make the preview heightmap slightly blue
            happy_file << static_cast <int> (floor(heightmap[i][k] * 0.85)) << ' ';
            happy_file << static_cast <int> (floor(heightmap[i][k] * 0.85)) << ' ';

            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << heightmap[i][k] << '\n';
            else happy_file << static_cast <int> (heightmap[i][k]) << ' ';

        }
    }

    happy_file.close();

}


// place the new layer button at the first inactive layer
void interface_noise_layers :: update_new_layer_button() {

    emit invalidate_heightmap_signal();

    sort_layers();

    if (!layers_vector[1] -> active) layers_vector[0] -> delete_layer_button -> setEnabled(false);
    else layers_vector[0] -> delete_layer_button -> setEnabled(true);

    for (int i = 1; i < NOISE_LAYERS; i++) {
        if (layers_vector[i - 1] -> active && !layers_vector[i] -> active) {
            layers_vector[i] -> display_button();
            for (int k = i + 1; k < NOISE_LAYERS; k++) layers_vector[k] -> deactivate_layer();
            return;
        }
    }
}


// active layers should stay on top
void interface_noise_layers :: sort_layers() {

    for (int i = 0; i < NOISE_LAYERS; i++) {
        box -> removeWidget(layers_vector[i]);
        if (i < (NOISE_LAYERS - 1) && !layers_vector[i] -> active && layers_vector[i + 1] -> active) {
            layers_vector[NOISE_LAYERS] = layers_vector[i];
            layers_vector[i] = layers_vector[i + 1];
            layers_vector[i + 1] = layers_vector[NOISE_LAYERS];
        }
    }

    for (int i = 0; i < NOISE_LAYERS; i++) {
        layers_vector[i] -> layer_label -> setText(QString("L" + QString :: number(i + 1)));
        box -> addWidget(layers_vector[i]);
    }
}


// unlock heightmap for reloading
void interface_noise_layers :: layer_state_changed() { emit invalidate_heightmap_signal(); }
