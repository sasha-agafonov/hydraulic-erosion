#include "interface_generation_menu.h"

generation_menu :: generation_menu(QWidget *parent) : QWidget(parent) {

    v_box = new QVBoxLayout(this);

    noise_parameters = new noise_parameters_menu(this);
    hydro_parameters = new hydro_parameters_menu(this);
    terrain_parameters = new terrain_parameters_menu(this);

    build_button = new QPushButton("Build Terrain", this);

    connect(build_button, SIGNAL(clicked()), parent, SLOT(load_scene()));

    v_box -> addWidget(terrain_parameters);
    v_box -> addWidget(noise_parameters);
    v_box -> addWidget(hydro_parameters);
    v_box -> addWidget(build_button);

    noisy = new noise();

}

void generation_menu :: reload_heightmap() {

    noise_parameters -> noise_layers_widget -> build_layers(terrain_parameters -> width_x_spinbox -> value(),
                                                            terrain_parameters -> width_y_spinbox -> value(),
                                                            terrain_parameters -> gradient_seed_checkbox -> isChecked());
}
