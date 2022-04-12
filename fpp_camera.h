#ifndef FPP_CAMERA_H
#define FPP_CAMERA_H

class fpp_camera {

public:

    fpp_camera(double horizontal_ang, double vertical_ang);

    double horizontal_ang;
    double vertical_ang;
    double view_radius;

    double look_at_x;
    double look_at_y;
    double look_at_z;

    double position_x;
    double position_y;
    double position_z;

    void set_angles(double horizontal_ang, double vertical_ang);
    void set_radius(double radius);
    void move_camera(bool forward, bool back, bool left, bool right, bool up, bool down);
    void look();

};

#endif // FPP_CAMERA_H
