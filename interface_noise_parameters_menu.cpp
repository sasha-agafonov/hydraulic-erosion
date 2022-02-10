#include "interface_noise_parameters_menu.h"

noise_parameters_menu :: noise_parameters_menu(QWidget *parent) : QWidget(parent) {

    box = new QHBoxLayout(this);
    grid = new QGridLayout(this);

    randgen_checkbox = new QCheckBox(this);

//    octaves_spinbox = new QSpinBox(this);
//        octaves_spinbox -> setMinimum(1);
//    octaves_spinbox -> setMaximum(10);


    tsize_w_spinbox = new QSpinBox(this);
    tsize_w_spinbox -> setMinimum(1);
    tsize_w_spinbox -> setMaximum(1000);

    tsize_h_spinbox = new QSpinBox(this);
    tsize_h_spinbox -> setMinimum(1);
    tsize_h_spinbox -> setMaximum(1000);

    frequency_slider = new QSlider(Qt :: Horizontal);
    frequency_slider -> setMaximum(10);
    frequency_slider -> setMinimum(1);

    persistence_slider = new QSlider(Qt :: Horizontal);
    persistence_slider -> setMaximum(10);
    persistence_slider -> setMinimum(1);

    lacunarity_slider = new QSlider(Qt :: Horizontal);
    lacunarity_slider -> setMaximum(10);
    lacunarity_slider -> setMinimum(1);

    scale_slider = new QSlider(Qt :: Horizontal);
    scale_slider -> setMaximum(10);
    scale_slider -> setMinimum(1);

    heightmap_widget = new heightmap_preview(this);

    grid -> addWidget(new QLabel("Terrain Size", this), 0, 0, 1, 1);
    grid -> addWidget(tsize_w_spinbox, 0, 1, 1, 1);
    grid -> addWidget(tsize_h_spinbox, 0, 2, 1, 1);

    grid -> addWidget(new QLabel("Randomized Parameters", this), 1, 0, 1, 1);
    grid -> addWidget(randgen_checkbox, 1, 1, 1, 1);

    grid -> addWidget(new QLabel("Frequency", this), 2, 0, 1, 1);
    grid -> addWidget(frequency_slider, 2, 1, 1, 2);

    grid -> addWidget(new QLabel("Scale", this), 3, 0, 1, 1);
    grid -> addWidget(scale_slider, 3, 1, 1, 2);

    grid -> addWidget(new QLabel("Persistence", this), 4, 0, 1, 1);
    grid -> addWidget(persistence_slider, 4, 1, 1, 2);

    grid -> addWidget(new QLabel("Lacunarity", this), 5, 0, 1, 1);
    grid -> addWidget(lacunarity_slider, 5, 1, 1, 2);

//    grid -> addWidget(new QLabel("Octaves", this), 6, 0, 1, 1);
//    grid -> addWidget(octaves_spinbox, 6, 1, 1, 1);


//    grid -> addWidget(build_button, 2, 0, 1, 1);
//    grid -> addWidget(randgen_button, 2, 1, 1, 1);

//    grid -> addWidget(randgen_checkbox, 3, 0, 1, 1);

//    grid -> addWidget(tsize_w_spinbox, 4, 0, 1, 1);
//    grid -> addWidget(tsize_h_spinbox, 4, 1, 1, 1);

   // grid -> addWidget(hmap_preview, 3, 0, 1, 1);

    box -> addLayout(grid);
    box -> addWidget(heightmap_widget);

}
