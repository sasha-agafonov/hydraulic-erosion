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

    noise_parameters_menu(QWidget *parent, int wx, int wy, bool random);

    QHBoxLayout* h_box;
    QVBoxLayout* v_box;
    QVBoxLayout* v_box_2;
    QGridLayout* grid;

    QLabel* noise_layers_label;
    QLabel* heightmap_preview_label;

    interface_noise_layers* noise_layers_widget;
    heightmap_preview* heightmap_widget;

public slots:

    void reload_heightmap();
    void invalidate_heightmap();

signals:

    void reload_heightmap_signal();
    void invalidate_eroded_heightmap_signal();

};

#endif // INTERFACE_NOISE_PARAMETERS_MENU_H
