#ifndef GRID_LAYOUT_H
#define GRID_LAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QBoxLayout>
#include <QObject>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QKeyEvent>


class grid_layout : public QWidget {

public:
    grid_layout(QWidget *parent);

    QGridLayout* grid;

    QSlider* persistence_slider;

    QLabel* persistence_label;

    QPushButton *paramgenerate_button, *randgenerate_button;
};

#endif // GRID_LAYOUT_H
