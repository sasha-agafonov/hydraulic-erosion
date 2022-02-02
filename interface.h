#ifndef INTERFACE_H
#define INTERFACE_H

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QBoxLayout>
#include <QObject>
#include <QTimer>
#include <QLabel>
#include <QGridLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QKeyEvent>
#include "world.h"
#include "grid_layout.h"

class interface : public QWidget {

    Q_OBJECT

public slots:
    void switch_window();

//signals:
//    void cu();

public:

    interface(QWidget *parent);

    ~interface();

    void main_menu();

    void world_view();

//    /void keyPressEvent(QKeyEvent* event);

    QMenuBar* menuBar;

    // file menu
    QMenu* fileMenu;

    // quit action
    QAction* actionQuit;

    QBoxLayout *box, *scene_box, *button_box;

    grid_layout* grid;

    QSlider* persistence_slider;

    QLabel* persistence_label;

    QPushButton *paramgenerate_button, *randgenerate_button;

    QTimer* timer;

    world* scene;

private:

    bool in_menu;



};


#endif // INTERFACE_H
