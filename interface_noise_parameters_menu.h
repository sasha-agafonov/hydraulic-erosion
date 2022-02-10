#ifndef INTERFACE_NOISE_PARAMETERS_MENU_H
#define INTERFACE_NOISE_PARAMETERS_MENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QObject>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>

#include "interface_heightmap_preview.h"


class noise_parameters_menu : public QWidget {

public:

    noise_parameters_menu(QWidget *parent);

    QHBoxLayout* box;
    QGridLayout* grid;

    QSpinBox* tsize_w_spinbox;
    QSpinBox* tsize_h_spinbox;
    //QSpinBox* octaves_spinbox;

    QCheckBox* randgen_checkbox;

    QSlider* frequency_slider;
    QSlider* persistence_slider;
    QSlider* lacunarity_slider;
    QSlider* scale_slider;

    QPushButton* build_button;

    heightmap_preview* heightmap_widget;

};

#endif // INTERFACE_NOISE_PARAMETERS_MENU_H
