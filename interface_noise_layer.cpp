#include <QLabel>
#include <QString>

#include "interface_noise_layer.h"


noise_layer :: noise_layer(QWidget* parent, int layer_number) : QFrame(parent) {

    this -> setStyleSheet("QFrame { background-color: rgba(60, 66, 78, 1); border-radius: 6px; padding: 0; }");

    box = new QHBoxLayout(this);

    layer_label = new QLabel(QString("Layer " + QString :: number(layer_number)), this);
    empty_label = new QLabel("Empty Layer Slot", this);
    scale_label = new QLabel("Scale", this);
    frequency_label = new QLabel("Frequency", this);
    persistence_label = new QLabel("Persistence", this);

    new_layer_button = new QPushButton("Add Layer", this);

    //new_layer_button -> setStyleSheet( "QPushButton { padding: 0; height: 25px; min-height: 4em;background: rgba(190, 190, 222, 1);border: 0;font-size: 11px; color: rgba(40, 44, 52, 1); }");

    delete_layer_button = new QPushButton("Delete Layer", this);

    scale_spinbox = new QSpinBox(this);
    scale_spinbox -> setMinimum(1);
    scale_spinbox -> setMaximum(10);

    frequency_spinbox = new QSpinBox(this);
    frequency_spinbox -> setMinimum(1);
    frequency_spinbox -> setMaximum(10);

    persistence_spinbox = new QSpinBox(this);
    persistence_spinbox -> setMinimum(1);
    persistence_spinbox -> setMaximum(10);

    connect(new_layer_button, SIGNAL(clicked()), this, SLOT(activate_layer()));
    connect(new_layer_button, SIGNAL(clicked()), parent, SLOT(update_new_layer_button()));

    connect(delete_layer_button, SIGNAL(clicked()), this, SLOT(deactivate_layer()));
    connect(delete_layer_button, SIGNAL(clicked()), parent, SLOT(update_new_layer_button()));

    box -> addWidget(layer_label);
    box -> addWidget(empty_label);
    box -> addWidget(new_layer_button);
    box -> addWidget(scale_label);
    box -> addWidget(scale_spinbox);
    box -> addWidget(frequency_label);
    box -> addWidget(frequency_spinbox);
    box -> addWidget(persistence_label);
    box -> addWidget(persistence_spinbox);
    box -> addWidget(delete_layer_button);

    new_layer_button -> hide();
    layer_label -> hide();
    scale_label -> hide();
    scale_spinbox -> hide();
    frequency_spinbox -> hide();
    frequency_label -> hide();
    persistence_spinbox -> hide();
    persistence_label -> hide();
    delete_layer_button -> hide();

    active = false;

}

void noise_layer :: activate_layer() {

    this -> setStyleSheet("QFrame { background-color: rgba(110, 110, 135, 1); border-radius: 6px; }");

    new_layer_button -> hide();
    empty_label -> hide();

    layer_label -> show();
    scale_label -> show();
    scale_spinbox -> show();
    frequency_label -> show();
    frequency_spinbox -> show();
    persistence_label -> show();
    persistence_spinbox -> show();
    delete_layer_button -> show();

    active = true;
}

void noise_layer :: deactivate_layer() {

    this -> setStyleSheet("QFrame { background-color: rgba(60, 66, 78, 1); border-radius: 6px; }");

    new_layer_button -> hide();

    layer_label -> hide();
    scale_label -> hide();
    scale_spinbox -> hide();
    frequency_label -> hide();
    frequency_spinbox -> hide();
    persistence_label -> hide();
    persistence_spinbox -> hide();

    empty_label -> show();

    active = false;
}

void :: noise_layer :: display_button() {

    this -> setStyleSheet("QFrame { background-color: rgba(190, 190, 222, 1); border-radius: 6px; padding: 0; }");

    empty_label -> hide();
    delete_layer_button -> hide();

    new_layer_button -> show();
}
