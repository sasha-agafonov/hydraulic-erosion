#ifndef INTERFACE_TERRAIN_PARAMETERS_MENU_H
#define INTERFACE_TERRAIN_PARAMETERS_MENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QObject>


class terrain_parameters_menu : public QWidget {

    Q_OBJECT

public:
    terrain_parameters_menu(QWidget* parent);

    QHBoxLayout* box;
    QSpinBox* width_x_spinbox;
    QSpinBox* width_y_spinbox;
    QLabel* terrain_size_label;

public slots:

    void equalize_size_x();
    void equalize_size_y();
};

#endif // INTERFACE_TERRAIN_PARAMETERS_MENU_H
