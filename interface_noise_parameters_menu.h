#ifndef INTERFACE_NOISE_PARAMETERS_MENU_H
#define INTERFACE_NOISE_PARAMETERS_MENU_H

#include <QWidget>
#include <QBoxLayout>
#include <QGridLayout>
#include <QObject>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>

#include "interface_heightmap_preview.h"
#include "interface_noise_layer.h"
#include "interface_noise_layers.h"


class noise_parameters_menu : public QWidget {

    Q_OBJECT

public:

    noise_parameters_menu(QWidget *parent);

//    void sort_layers();

    //void new_layer_button();

    QHBoxLayout* h_box;
    QVBoxLayout* v_box;
    QVBoxLayout* v_box_2;
    QGridLayout* grid;

    QLabel* noise_layers_label;
    QLabel* heightmap_preview_label;

//    QSpinBox* tsize_w_spinbox;
//    QSpinBox* tsize_h_spinbox;
//    //QSpinBox* octaves_spinbox;

//    QCheckBox* randgen_checkbox;

//    QSlider* frequency_slider;
//    QSlider* persistence_slider;
//    QSlider* lacunarity_slider;
//    QSlider* scale_slider;

//    QPushButton* build_button;
    interface_noise_layers* noise_layers_widget;
    heightmap_preview* heightmap_widget;

public slots:

    void reload_heightmap();

signals:

    void reload_heightmap_signal();

//    noise_layer* layer1;
//    noise_layer* layer2;
//    noise_layer* layer3;
//    noise_layer* layer4;
//    noise_layer* layer5;
//    noise_layer* layer6;
//    noise_layer* layer7;
//    noise_layer* layer8;
//    noise_layer* layer9;
//    noise_layer* layer10;

   // std :: vector <noise_layer*> noise_layers;

//public slots:

//    void update_new_layer_button();

};

#endif // INTERFACE_NOISE_PARAMETERS_MENU_H
