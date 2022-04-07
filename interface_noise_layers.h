#ifndef INTERFACE_NOISE_LAYERS_H
#define INTERFACE_NOISE_LAYERS_H

#include <QWidget>
#include <QObject>
#include <QVBoxLayout>

#include "interface_noise_layer.h"
#include "noise_layer.h"

class interface_noise_layers : public QWidget {

    Q_OBJECT

public:

    interface_noise_layers(QWidget* parent, int wx, int wy, bool random);

    void sort_layers();
    void build_layers(int width, int height, bool random);

    QVBoxLayout* box;
    QLabel* noise_layers_label;

    std :: vector <interface_noise_layer*> layers_vector;

    noise_layer* alpha_map;

public slots:

    void update_new_layer_button();
    void layer_state_changed();

signals:
    void invalidate_heightmap_signal();
};

#endif // INTERFACE_NOISE_LAYERS_H
