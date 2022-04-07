#include <QMovie>

#include "interface_eroded_heightmap_preview.h"

eroded_heightmap_preview :: eroded_heightmap_preview(QWidget *parent) : QWidget(parent) {

    this -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);

    QPixmap pixmap("../terrain/heightmap_preview.ppm");

    box = new QVBoxLayout(this);
    box -> setAlignment(Qt :: AlignTop);
    box -> setSpacing(6);
    box -> setContentsMargins(11, 0, 0, 0);

    preview_label = new QLabel("Eroded Heightmap Preview", parent);
    preview_label -> setAlignment(Qt::AlignCenter);
    preview_label -> setFixedHeight(30);
    preview_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1);  height: 30px; margin: 0;}");



//    QMovie *movie = new QMovie("../terrain/ringer_sm2.gif");
//    QLabel *label = new QLabel(this);
//    label -> setStyleSheet("QLabel { background-color: rgba(1,1,1,0); } ");
//    label -> setMovie(movie);


    label = new QLabel();
    label -> setPixmap(pixmap.scaled(318, 318, Qt :: KeepAspectRatio));
    label -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);

    reload_button = new QPushButton("Currently up-to-date", this);
    reload_button -> setEnabled(false);
    reload_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                   "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    connect(reload_button, SIGNAL(clicked()), parent, SLOT(erode_heightmap()));

    reload_button -> setEnabled(true);

    box -> addWidget(preview_label);
    box -> addWidget(label);
    box -> addWidget(reload_button);
}

void eroded_heightmap_preview :: reload_heightmap() {

    this -> reload_button -> setEnabled(false);
    this -> reload_button -> setText("Currently up-to-date");
    this -> reload_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(110, 110, 135, 1); border: 0; margin: 0; border-radius: 6px; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                   "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");
    QPixmap pixmap("../terrain/heightmap_preview.ppm");

    label -> setPixmap(pixmap.scaled(318, 318, Qt :: KeepAspectRatio));
}
