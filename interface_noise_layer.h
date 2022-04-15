#ifndef INTERFACE_NOISE_LAYER_H
#define INTERFACE_NOISE_LAYER_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QObject>
#include <QSpacerItem>

#include "noise_layer.h"


class interface_noise_layer : public QFrame {

    Q_OBJECT

public:

    interface_noise_layer(QWidget* parent, int layer_number);

    QHBoxLayout* box;

    QPushButton* delete_layer_button;
    QPushButton* new_layer_button;

    QSpinBox* frequency_spinbox;
    QSpinBox* amplitude_spinbox;

    QComboBox* noise_type_combo;

    QLabel* layer_label;
    QLabel* empty_label;
    QLabel* amplitude_label;
    QLabel* frequency_label;

    QSpacerItem* space_1;
    QSpacerItem* space_2;
    QSpacerItem* space_3;

    noise_layer* noise;

    bool active;

public slots:

    void activate_layer();
    void deactivate_layer();
    void display_button();

};

#endif // INTERFACE_NOISE_LAYER_H
