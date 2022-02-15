#include "interface_heightmap_preview.h"

heightmap_preview :: heightmap_preview(QWidget *parent) : QWidget(parent) {

    this -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);

//    QPixmap pixmap("../terrain/heightmap_preview.ppm");

    QPixmap pixmap("../terrain/heightmap2.pgm");

    box -> setAlignment(Qt :: AlignTop);
    box = new QVBoxLayout(this);
    box -> setSpacing(15);
    box -> setContentsMargins(10, 0, 0, 0);

    preview_label = new QLabel("Heightmap Preview", parent);
    preview_label -> setAlignment(Qt::AlignCenter);
    preview_label -> setFixedHeight(30);
    preview_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1);  height: 30px; margin: 0;}");

    label = new QLabel();
    label -> setPixmap(pixmap.scaled(390, 390, Qt :: KeepAspectRatio));
    label -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);

    reload_button = new QPushButton("Reload heightmap", this);
    reload_button -> setStyleSheet("QPushButton { height: 30px; min-height: 2em; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                   "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    connect(reload_button, SIGNAL(clicked()), parent, SLOT(reload_heightmap()));
    connect(reload_button, SIGNAL(clicked()), this, SLOT(reload_heightmap()));

    reload_button -> setEnabled(true);

    box -> addWidget(preview_label);
    box -> addWidget(label);
    box -> addWidget(reload_button);

    noisy = new noise();
}

void heightmap_preview :: reload_heightmap() {

    reload_button -> setEnabled(true);

    QPixmap pixmap("../terrain/heightmap2.pgm");
    label -> setPixmap(pixmap.scaled(390, 390, Qt :: KeepAspectRatio));

    reload_button -> setEnabled(true);
}
