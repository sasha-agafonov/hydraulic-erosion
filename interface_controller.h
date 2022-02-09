#ifndef INTERFACE_CONTROLLER_H
#define INTERFACE_CONTROLLER_H

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
#include <QStackedLayout>

#include "world.h"
#include "grid_layout.h"
#include "scene_menu.h"
#include "loading_menu.h"
#include "generation_menu.h"
#include "splash_screen.h"

class interface_controller : public QWidget {

    Q_OBJECT

public slots:

    void toggle_scene_menu();
    void load_scene();
    void reload_scene();
    void exit_scene();
    void scene_ready();


//signals:
//    void cu();

public:

    interface_controller(QWidget *parent);

    ~interface_controller();

    void main_menu();

    void world_view();

       void test();

//    /void keyPressEvent(QKeyEvent* event);

    QMenuBar* menuBar;

    // file menu
    QMenu* fileMenu;

    // quit action
    QAction* actionQuit;
    QVBoxLayout *box;

    QStackedLayout* stack;

    QBoxLayout *scene_box, *button_box;

    grid_layout* grid;

    scene_menu* sc_menu;
    generation_menu* gen_menu;
    loading_menu* ldg_menu;

    splash_screen* splash;

    QSlider* persistence_slider;

    QLabel* persistence_label;

    QPushButton *paramgenerate_button, *randgenerate_button;

    QComboBox* antialiasing_combo;

    QTimer *timer, *timer2;

    world* scene;

private:

    bool in_menu;

};


#endif // INTERFACE_CONTROLLER_H
