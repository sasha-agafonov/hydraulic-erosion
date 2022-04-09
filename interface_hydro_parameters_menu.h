#ifndef INTERFACE_HYDRO_PARAMETERS_MENU_H
#define INTERFACE_HYDRO_PARAMETERS_MENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QObject>
#include <QLabel>
#include <QObject>
#include <QSlider>
#include <QCheckBox>
#include <QSpinBox>
#include <QTimer>

#include "interface_eroded_heightmap_preview.h"
#include "hydro.h"
#include "hydro2.h"
#include "hydro3.h"

class hydro_parameters_menu : public QWidget {

    Q_OBJECT

public:

    hydro_parameters_menu(QWidget *parent);

    QHBoxLayout* h_box;
    QVBoxLayout* v_box;
    QGridLayout* grid;

    QCheckBox* random_checkbox;

    QSlider* cycles_slider;
    QSlider* water_amount_slider;
    QSlider* carrying_capacity_slider;
    QSlider* evaporation_rate_slider;
    QSlider* erosion_rate_slider;
    QSlider* deposition_rate_slider;

    QSpinBox* cycles_spinbox;

    QLabel* random_label;
    QLabel* hydro_parameters_label;
    QLabel* cycles_label;
    QLabel* water_amount_label;
    QLabel* carrying_capacity_label;
    QLabel* evaporation_rate_label;
    QLabel* erosion_rate_label;
    QLabel* deposition_rate_label;

    QTimer* timer;

    hydro* hydraulic_erosion;
    hydro2* hydraulic_erosion2;
    hydro3* hydraulic_erosion3;
    eroded_heightmap_preview* eroded_heightmap;

    void original_heightmap_invalid();
    void original_heightmap_changed();

public slots:

    void erosion_parameters_changed();
    void erode_heightmap();
    void reload_heightmap();

};

#endif // INTERFACE_HYDRO_PARAMETERS_MENU_H
