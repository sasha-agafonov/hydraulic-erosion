#include <QMovie>

#include "interface_eroded_heightmap_preview.h"

eroded_heightmap_preview :: eroded_heightmap_preview(QWidget *parent) : QWidget(parent) {

    this -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);

    box = new QVBoxLayout(this);
    box -> setAlignment(Qt :: AlignTop);
    box -> setSpacing(6);
    box -> setContentsMargins(11, 0, 0, 0);

    preview_label = new QLabel("Eroded Heightmap Preview", parent);
    preview_label -> setAlignment(Qt::AlignCenter);
    preview_label -> setFixedHeight(30);
    preview_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1);  height: 30px; margin: 0;}");

    label = new QLabel("Heightmap not eroded yet");
    label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(60, 66, 78, 1); height: 30px; margin: 0; }");
    label -> setFixedWidth(318);
    label -> setFixedHeight(318);
    label -> setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    label -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);

    reload_button = new QPushButton("Please generate a heightmap first", this);
    reload_button -> setEnabled(false);
    reload_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                   "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    connect(reload_button, SIGNAL(clicked()), parent, SLOT(erode_heightmap()));
    connect(this, SIGNAL(eroded_heightmap_valid_signal()), parent, SLOT(eroded_heightmap_valid()));

    box -> addWidget(preview_label);
    box -> addWidget(label);
    box -> addWidget(reload_button);

    ready = false;
}


void eroded_heightmap_preview :: reload_heightmap() {

    this -> reload_button -> setEnabled(false);
    this -> reload_button -> setText("Currently up-to-date");
    this -> reload_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                   "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    QPixmap pixmap("../terrain/heightmap_eroded_preview.ppm");

    if (!(pixmap.isNull())) {
        label -> setPixmap(pixmap.scaled(318, 318, Qt :: KeepAspectRatio));
    } else label -> setText("No heightmap");

    emit eroded_heightmap_valid_signal();
}
