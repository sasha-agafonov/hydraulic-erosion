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

#include "noise.h"
#include "terrain.h"
#include "fpp_camera.h"

#define BASE_DIM 10

class world : public QGLWidget {

    Q_OBJECT

public slots:
    void update_scene();
    void resetFPS();
    void cameraUpdate(double x, double y, double z);

public:
    world(QGLFormat format, QWidget *parent);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    noise* noisy;
    fpp_camera* camera;

    //QPainter* painter;

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    int fps;
    //void paintEvent(QPaintEvent* event);

private:

    void load_terrain();
    void draw_terrain();

    void convert_to_spherical(double x, double y);
    void reload();




    double cs_vector_y(double x1, double x2, double y1, double z1, double z2, double dist);

    double view_x, view_y, view_z;

    int tick;
    int zoom;
    int* terrarray;

    double cx, cy, cz;

    double mouse_prev_pos_x;
    double mouse_prev_pos_y;

    double camera_position_x;
    double camera_position_y;
    double camera_position_z;

    double direction_x;
    double direction_y;
    double direction_z;

    double shake;
    bool shake_right, jump;

    QPoint mouse_position;
    double cursor_x;
    double cursor_y;
    double spherical_x;
    double spherical_y;

    bool forward;
    bool back;
    bool left;
    bool right;
    bool up;
    bool down;
    bool menu;

    terrain* terra;

    void icosahedron();

    double vectorLength(double a, double b, double c);

    std :: vector <int> numeric;

    std :: vector < std :: vector <int> > terrain_mx;



};


#endif // WORLD_H
