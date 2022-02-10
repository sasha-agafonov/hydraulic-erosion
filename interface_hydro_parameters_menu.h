#ifndef INTERFACE_HYDRO_PARAMETERS_MENU_H
#define INTERFACE_HYDRO_PARAMETERS_MENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QObject>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>

class hydro_parameters_menu : public QWidget {

public:

    hydro_parameters_menu(QWidget *parent);

    QHBoxLayout* box;
    QGridLayout* grid;

    QSlider* water_amount;
    QSlider* cycles;
    QSlider* evap_rate;

    QSlider* erosion_rate;
    QSlider* carry_cap;
    QCheckBox* random_checkbox;
};

#endif // INTERFACE_HYDRO_PARAMETERS_MENU_H
