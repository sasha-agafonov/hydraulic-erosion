#include "interface_generation_menu.h"

generation_menu :: generation_menu(QWidget *parent) : QWidget(parent) {

    box = new QVBoxLayout(this);

    noise_parameters = new noise_parameters_menu(this);
    hydro_parameters = new hydro_parameters_menu(this);

   // hydro_parameters -> box -> setMargin(0);

    build_button = new QPushButton("Build Terrain", this);

    connect(build_button, SIGNAL(clicked()), parent, SLOT(load_scene()));

    box -> addWidget(noise_parameters);
    box -> addWidget(hydro_parameters);
    box -> addWidget(build_button);

}
