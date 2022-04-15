#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QGLWidget>
#include <QKeyEvent>
#include <QPoint>
#include <vector>
#include <QGLFormat>
#include <QGridLayout>
#include <QPainter>

#include "terrain.h"
#include "fpp_camera.h"
#include "interface_splash_screen.h"

#define BASE_DIM 10

class world : public QGLWidget {

    Q_OBJECT

public:

    world( QWidget *parent);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    terrain* bad_terrain;
    fpp_camera* camera;

    int fps, fps_counter;
    int sc_width, sc_height;

    double cursor_x;
    double cursor_y;

signals:

    void exit_signal();

public slots:

    void resetFPS();
    void update_scene();

private:

    bool forward;
    bool back;
    bool left;
    bool right;
    bool up;
    bool down;
    bool show_fps;

};

#endif // WORLD_H
