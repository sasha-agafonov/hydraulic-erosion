#ifndef INTERFACE_DOUBLE_SLIDER_H
#define INTERFACE_DOUBLE_SLIDER_H

#include <QSlider>
#include <QWidget>


class interface_double_slider : public QSlider {

    Q_OBJECT

public:

    interface_double_slider(Qt :: Orientation orientation, QWidget* parent = 0);

public slots:

    void value_changed_double(int value);
    void set_double_value(double);

signals:

    double value_changed_double_signal(double);

};

#endif // INTERFACE_DOUBLE_SLIDER_H
