#ifndef INTERFACE_SCENE_MENU_H
#define INTERFACE_SCENE_MENU_H

#include <QWidget>
#include <QGridLayout>
#include <QObject>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>


class scene_menu : public QWidget {

    Q_OBJECT

public:

    scene_menu(QWidget *parent);

    QGridLayout* grid;

    QSlider* fov_slider;
    QSlider* distance_slider;
    QSlider* sensitivity_slider;

    QComboBox* antialiasing_combo;
    QComboBox* fps_lock_combo;

    QCheckBox* fps_toggle_checkbox;
    QCheckBox* flat_shading_checkbox;

    QLabel* fov_label;
    QLabel* distance_label;
    QLabel* sensitivity_label;
    QLabel* antialiasing_label;
    QLabel* fps_lock_label;
    QLabel* fps_toggle_label;
    QLabel* flat_shading_label;

    QPushButton* save_button;
    QPushButton* exit_button;

};

#endif // INTERFACE_SCENE_MENU_H
