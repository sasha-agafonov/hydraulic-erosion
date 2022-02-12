#ifndef INTERFACE_NOISE_LAYER_H
#define INTERFACE_NOISE_LAYER_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QObject>


class noise_layer : public QFrame {

    Q_OBJECT

public:

    noise_layer(QWidget* parent, int layer_number);

    QHBoxLayout* box;

    QPushButton* delete_layer_button;
    QPushButton* new_layer_button;

    QSpinBox* scale_spinbox;
    QSpinBox* frequency_spinbox;
    QSpinBox* persistence_spinbox;

    QLabel* layer_label;
    QLabel* empty_label;
    QLabel* scale_label;
    QLabel* frequency_label;
    QLabel* persistence_label;

    bool active;

public slots:

    void activate_layer();
    void deactivate_layer();
    void display_button();

};

#endif // INTERFACE_NOISE_LAYER_H
