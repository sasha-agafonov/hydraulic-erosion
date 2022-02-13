#ifndef INTERFACE_NOISE_LAYERS_H
#define INTERFACE_NOISE_LAYERS_H

#include <QWidget>
#include <QObject>
#include <QVBoxLayout>

#include "interface_noise_layer.h"

class interface_noise_layers : public QWidget {

    Q_OBJECT

public:

    interface_noise_layers(QWidget* parent);

    void sort_layers();
    void build_layers(int width, int height);
    //void create_heightmap(int width, int height);

    QVBoxLayout* box;

    QLabel* noise_layers_label;

    std :: vector <interface_noise_layer*> layers_vector;

public slots:

    void update_new_layer_button();
};

#endif // INTERFACE_NOISE_LAYERS_H
