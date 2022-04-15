#include "interface_heightmap_preview.h"

heightmap_preview :: heightmap_preview(QWidget *parent) : QWidget(parent) {

    this -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);

    box = new QVBoxLayout(this);
    box -> setAlignment(Qt :: AlignTop);
    box -> setSpacing(6);
    box -> setContentsMargins(11, 0, 0, 0);

    preview_label = new QLabel("Heightmap Preview", parent);
    preview_label -> setAlignment(Qt::AlignCenter);
    preview_label -> setFixedHeight(30);
    preview_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1);  margin: 0;}");

    label = new QLabel("No heightmap generated yet");
    label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(60, 66, 78, 1); height: 30px; margin: 0; }");
    label -> setFixedWidth(318);
    label -> setFixedHeight(318);
    label -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);
    label -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);

    reload_button = new QPushButton("Press to generate a heightmap", this);
    reload_button -> setFixedHeight(30);
    reload_button -> setEnabled(true);
    reload_button -> setStyleSheet("QPushButton { height: 30px; background-color: rgba(190, 190, 222, 1);border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                   "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    connect(reload_button, SIGNAL(clicked()), parent, SLOT(reload_heightmap()));
    connect(reload_button, SIGNAL(clicked()), this, SLOT(reload_heightmap()));
    connect(this, SIGNAL(heightmap_valid_signal()), parent, SLOT(heightmap_valid()));

    box -> addWidget(preview_label);
    box -> addWidget(label);
    box -> addWidget(reload_button);

    ready = true;

}

void heightmap_preview :: reload_heightmap() {

    QPixmap pixmap("../terrain/heightmap_preview.ppm");
    label -> setPixmap(pixmap.scaled(318, 318, Qt :: KeepAspectRatio));
    ready = true;

    emit heightmap_valid_signal();

}
