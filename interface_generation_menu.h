#ifndef INTERFACE_GENERATION_MENU_H
#define INTERFACE_GENERATION_MENU_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QObject>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>

#include "interface_noise_parameters_menu.h"
#include "interface_hydro_parameters_menu.h"


class generation_menu : public QWidget {

    Q_OBJECT

public:

    generation_menu(QWidget *parent);

    QVBoxLayout* box;
    QPushButton* build_button;

    noise_parameters_menu* noise_parameters;
    hydro_parameters_menu* hydro_parameters;

};

#endif // INTERFACE_GENERATION_MENU_H
