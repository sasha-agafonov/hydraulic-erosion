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
#include <QDoubleSpinBox>
#include <QTimer>

#include "interface_eroded_heightmap_preview.h"
#include "interface_double_slider.h"
#include "hydro.h"

class hydro_parameters_menu : public QWidget {

    Q_OBJECT

public:

    hydro_parameters_menu(QWidget *parent);

    QHBoxLayout* h_box;
    QVBoxLayout* v_box;
    QGridLayout* grid;

    QCheckBox* random_checkbox;

    QSlider* cycles_slider;
    interface_double_slider* water_amount_slider;
    interface_double_slider* carrying_capacity_slider;
    interface_double_slider* evaporation_rate_slider;
    interface_double_slider* erosion_rate_slider;
    interface_double_slider* deposition_rate_slider;
    interface_double_slider* post_evaporation_rate_slider;

    QSpinBox* cycles_spinbox;
    QDoubleSpinBox* water_spinbox;
    QDoubleSpinBox* carry_spinbox;
    QDoubleSpinBox* erosion_spinbox;
    QDoubleSpinBox* deposition_spinbox;
    QDoubleSpinBox* evaporation_spinbox;
    QDoubleSpinBox* post_evaporation_spinbox;

    QLabel* random_label;
    QLabel* hydro_parameters_label;
    QLabel* cycles_label;
    QLabel* water_amount_label;
    QLabel* carrying_capacity_label;
    QLabel* evaporation_rate_label;
    QLabel* erosion_rate_label;
    QLabel* post_evaporation_rate_label;
    QLabel* deposition_rate_label;

    QTimer* timer;

    hydro* hydraulic_erosion;

    eroded_heightmap_preview* eroded_heightmap;

    void original_heightmap_invalid();
    void original_heightmap_changed();

public slots:

    void erosion_parameters_changed();
    void erode_heightmap();
//    void reload_heightmap();
    void eroded_heightmap_valid();

signals:

    void eroded_heightmap_valid_signal();

};

#endif // INTERFACE_HYDRO_PARAMETERS_MENU_H
