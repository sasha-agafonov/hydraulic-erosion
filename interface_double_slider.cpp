#include "interface_double_slider.h"
#include <iostream>


interface_double_slider :: interface_double_slider(Qt :: Orientation orientation, QWidget* parent) : QSlider(orientation, parent) {

    connect(this, SIGNAL(valueChanged(int)), this, SLOT(value_changed_double(int)));

}


void interface_double_slider :: value_changed_double(int value) {

    double double_value = value;

    emit value_changed_double_signal(double_value / 100);

}


void interface_double_slider :: set_double_value(double value) {

    this -> setValue(value * 100);

}
