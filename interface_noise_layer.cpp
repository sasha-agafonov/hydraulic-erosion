#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QListView>

#include "interface_noise_layer.h"


interface_noise_layer :: interface_noise_layer(QWidget* parent, int layer_number) : QFrame(parent) {

    this -> setStyleSheet("QFrame { background-color: rgba(60, 66, 78, 1); border-radius: 6px; padding: 0; }");
    this -> setFixedHeight(30);

    box = new QHBoxLayout(this);
    box -> setContentsMargins(0, 0, 0, 0);

    layer_label = new QLabel(QString("L" + QString :: number(layer_number)), this);
    layer_label -> setStyleSheet("QLabel { color: rgba(40, 44, 52, 1); background-color: rgba(190, 190, 222, 1); padding-left: 12px; border-radius: 0; border-top-left-radius: 6px; border-bottom-left-radius: 6px; }");
    layer_label -> setFixedWidth(44);

    empty_label = new QLabel("Empty Slot", this);
    empty_label -> setAlignment(Qt::AlignCenter);

    frequency_label = new QLabel("Frequency", this);
    frequency_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(1, 1, 1, 0); padding-right: 6px; }");
    frequency_label -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    amplitude_label = new QLabel("Amplitude", this);
    amplitude_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(1, 1, 1, 0); padding-right: 6px; }");
    amplitude_label -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    new_layer_button = new QPushButton("Add Layer", this);
    new_layer_button -> setStyleSheet("QPushButton { height: 30px; background: rgba(190, 190, 222, 1); border: 0; margin: 0; border-radius: 6px; font-size: 12px; color: rgba(40, 44, 52, 1); } "
                                      "QPushButton:pressed { background: rgba(110, 110, 135, 1); }");

    delete_layer_button = new QPushButton(this);
    delete_layer_button -> setSizePolicy(QSizePolicy :: Fixed, QSizePolicy :: Fixed);
    delete_layer_button -> setIcon(QIcon("../terrain/delete_button.png"));
    delete_layer_button -> setIconSize(QSize(20, 20));
    delete_layer_button -> setStyleSheet("QPushButton { height: 30px; width: 44px; background: rgba(190, 190, 222, 1);  border-top-right-radius: 6px; border-bottom-right-radius: 6px; border-bottom-left-radius: 0px; border-top-left-radius: 0px; font-size: 11px; color: rgba(40, 44, 52, 1); margin-left: 10px; }"
                                         "QPushButton:pressed { background: rgba(110, 110, 135, 1); }");

    frequency_spinbox = new QSpinBox(this);
    frequency_spinbox -> setMinimum(1);
    frequency_spinbox -> setMaximum(500);
    frequency_spinbox -> setFixedWidth(50);
    frequency_spinbox -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    amplitude_spinbox = new QSpinBox(this);
    amplitude_spinbox -> setMinimum(1);
    amplitude_spinbox -> setMaximum(500);
    amplitude_spinbox -> setFixedWidth(50);
    amplitude_spinbox -> setValue(100);
    amplitude_spinbox -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    noise = new noise_layer();

    space_1 = new QSpacerItem(1000, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);
    space_2 = new QSpacerItem(1000, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);
    space_3 = new QSpacerItem(1000, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

    connect(new_layer_button, SIGNAL(clicked()), this, SLOT(activate_layer()));
    connect(new_layer_button, SIGNAL(clicked()), parent, SLOT(update_new_layer_button()));

    connect(delete_layer_button, SIGNAL(clicked()), this, SLOT(deactivate_layer()));
    connect(delete_layer_button, SIGNAL(clicked()), parent, SLOT(update_new_layer_button()));

    connect(frequency_spinbox, SIGNAL(valueChanged(int)), parent, SLOT(layer_state_changed()));
    connect(amplitude_spinbox, SIGNAL(valueChanged(int)), parent, SLOT(layer_state_changed()));

    box -> addWidget(layer_label);
    box -> addItem(space_1);
    box -> addWidget(frequency_label);
    box -> addWidget(frequency_spinbox);
    box -> addItem(space_2);
    box -> addWidget(amplitude_label);
    box -> addWidget(amplitude_spinbox);
    box -> addItem(space_3);
    box -> addWidget(delete_layer_button);
    box -> addWidget(empty_label);
    box -> addWidget(new_layer_button);

    new_layer_button -> hide();
    layer_label -> hide();
    frequency_spinbox -> hide();
    frequency_label -> hide();
    amplitude_label -> hide();
    amplitude_spinbox -> hide();
    delete_layer_button -> hide();

    active = false;

    this -> setLayout(box);

}

void interface_noise_layer :: activate_layer() {

    this -> setStyleSheet("QFrame { background-color: rgba(110, 110, 135, 1); border-radius: 6px; padding: 0; height: 30px; }");

    space_1 -> changeSize(1000, 10);
    space_2 -> changeSize(1000, 10);
    space_3 -> changeSize(1000, 10);
    new_layer_button -> hide();
    empty_label -> hide();
    layer_label -> show();
    frequency_label -> show();
    frequency_spinbox -> show();
    amplitude_label -> show();
    amplitude_spinbox -> show();
    delete_layer_button -> show();

    active = true;
}

void interface_noise_layer :: deactivate_layer() {

    this -> setStyleSheet("QFrame { background-color: rgba(60, 66, 78, 1); border-radius: 6px; padding: 0; height: 30px; }");

    space_1 -> changeSize(0, 0);
    space_2 -> changeSize(0, 0);
    space_3 -> changeSize(0, 0);
    new_layer_button -> hide();
    layer_label -> hide();
    frequency_label -> hide();
    frequency_spinbox -> hide();
    amplitude_label -> hide();
    amplitude_spinbox -> hide();
    empty_label -> show();

    active = false;
}

void interface_noise_layer :: display_button() {

    this -> setStyleSheet("QFrame { background-color: rgba(190, 190, 222, 1); border-radius: 6px; padding: 0; height: 30px; }");

    empty_label -> hide();
    delete_layer_button -> hide();
    new_layer_button -> show();
}
