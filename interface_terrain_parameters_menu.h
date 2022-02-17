#ifndef INTERFACE_TERRAIN_PARAMETERS_MENU_H
#define INTERFACE_TERRAIN_PARAMETERS_MENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QObject>
#include <QCheckBox>


class terrain_parameters_menu : public QWidget {

    Q_OBJECT

public:

    terrain_parameters_menu(QWidget* parent);

    QHBoxLayout* h_box_1;
    QHBoxLayout* h_box_2;
    QHBoxLayout* h_box_3;
    QVBoxLayout* v_box;

    QSpinBox* width_x_spinbox;
    QSpinBox* width_y_spinbox;

    QCheckBox* gradient_seed_checkbox;
    QCheckBox* materials_checkbox;

    QLabel* terrain_size_label;
    QLabel* gradient_seed_label;
    QLabel* materials_label;

public slots:

    void equalize_size_x();
    void equalize_size_y();

};

#endif // INTERFACE_TERRAIN_PARAMETERS_MENU_H
