#ifndef FPP_CAMERA_H
#define FPP_CAMERA_H

class fpp_camera {

public:

    fpp_camera(double horizontal_ang, double vertical_ang);
    void set_angles(double horizontal_ang, double vertical_ang);
    void set_radius(double radius);
    void move_camera(bool forward, bool back, bool left, bool right, bool up, bool down);
    void look();
    void point_of_view();
    bool multi_or(bool alpha, bool beta, bool delta, bool gamma);
    bool exclusive_or(bool alpha, bool beta);
//    void look_at_x();
//    void look_at_y();
//    void look_at_z();
    double shake();
    bool shaking;

    double horizontal_ang;
    double vertical_ang;
    double view_radius;

    double look_at_x;
    double look_at_y;
    double look_at_z;

    double position_x;
    double position_y;
    double position_z;

//    typedef struct lk {
//        double look_at_x;
//        double look_at_y;
//        double look_at_z;
//    } look;

//    typedef struct pos {
//        double position_x;
//        double position_y;
//        double position_z;
//    } position;

private:

};

#endif // FPP_CAMERA_H
