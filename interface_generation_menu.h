#ifndef INTERFACE_GENERATION_MENU_H
#define INTERFACE_GENERATION_MENU_H

#include <QWidget>
#include <QGridLayout>
#include <QBoxLayout>
#include <QObject>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>

#include "interface_noise_parameters_menu.h"
#include "interface_hydro_parameters_menu.h"
#include "interface_terrain_parameters_menu.h"

#include "noise.h"
#include "noise_layer.h"
#include "hydro.h"


class generation_menu : public QWidget {

    Q_OBJECT

public:

    generation_menu(QWidget *parent);

    QVBoxLayout* v_box;
    QHBoxLayout* h_box;

    QPushButton* build_uneroded_button;
    QPushButton* build_eroded_button;
    QPushButton* build_and_erode_button;

    noise_parameters_menu* noise_parameters;
    hydro_parameters_menu* hydro_parameters;
    terrain_parameters_menu* terrain_parameters;

    noise* noisy;
    hydro* water;
    noise_layer* layer;

public slots:

    void reload_heightmap();
    void terrain_changed();
    void invalidate_eroded_heightmap();

signals:

    void invalidate_heightmap_signal();


};

#endif // INTERFACE_GENERATION_MENU_H
