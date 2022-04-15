#ifndef INTERFACE_CONTROLLER_H
#define INTERFACE_CONTROLLER_H

#include <QGLWidget>
#include <QBoxLayout>
#include <QObject>
#include <QTimer>

#include "world.h"
#include "interface_generation_menu.h"
#include "interface_splash_screen.h"


class interface_controller : public QWidget {

    Q_OBJECT

public slots:

    void load_scene();
    void exit_scene();

    void load_eroded();
    void load_uneroded();
    void load_and_erode();

public:

    interface_controller(QWidget *parent);

    ~interface_controller();

    void main_menu();
    void world_view();
    void test();

    QTimer *timer, *timer2;
    QVBoxLayout *box;

    generation_menu* gen_menu;
    splash_screen* splash;
    world* scene;

};


#endif // INTERFACE_CONTROLLER_H
