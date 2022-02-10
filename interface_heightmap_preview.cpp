#include "interface_heightmap_preview.h"

heightmap_preview :: heightmap_preview(QWidget *parent) : QWidget(parent) {

    QPixmap pixmap("../terrain/heightmap_preview.ppm");

    box = new QVBoxLayout(this);

    label = new QLabel();
    label -> setPixmap(pixmap);

    reload_button = new QPushButton("Reload heightmap", this);
    reload_button -> setStyleSheet("QPushButton { height: 16px; min-height: 2em; background: rgba(190, 190, 222, 1); border: 0; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                   "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    connect(reload_button, SIGNAL(clicked()), this, SLOT(reload_heightmap()));

    box -> addWidget(label);
    box -> addWidget(reload_button);

    noisy = new noise();
}

void heightmap_preview :: reload_heightmap() {

    noisy -> create_vector_grid(10, 10);
    noisy -> normalize_gradients();


    noisy -> map_samples(300, 300);
    noisy -> perlin_noise();

    noisy -> black_noise();

    noisy -> create_heightmap();
    noisy -> create_preview_heightmap();

//       noisy -> map_samples2(500, 500);
//       noisy -> create_map();
//       noisy -> create_heightmap2();




    // generate new img by telling qopenglw to generate new img

    QPixmap pixmap("../terrain/heightmap_preview.ppm");
    label -> setPixmap(pixmap);
}
