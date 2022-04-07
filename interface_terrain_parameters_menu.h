#ifndef INTERFACE_TERRAIN_PARAMETERS_MENU_H
#define INTERFACE_TERRAIN_PARAMETERS_MENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QObject>
#include <QCheckBox>
#include <QGridLayout>


class terrain_parameters_menu : public QWidget {

    Q_OBJECT

public:

    terrain_parameters_menu(QWidget* parent);

    QHBoxLayout* box;

    QGridLayout* grid;

    QSpinBox* width_x_spinbox;
    QSpinBox* width_y_spinbox;

    QCheckBox* gradient_seed_checkbox;
//    QCheckBox* materials_checkbox;

    QLabel* terrain_parameters_label;
    QLabel* terrain_size_label;
    QLabel* gradient_seed_label;
//    QLabel* materials_label;

public slots:

    void equalize_size_x();
    void equalize_size_y();

};

#endif // INTERFACE_TERRAIN_PARAMETERS_MENU_H
