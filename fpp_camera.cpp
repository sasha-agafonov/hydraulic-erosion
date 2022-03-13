#include <cmath>
#include <iostream>
#include "fpp_camera.h"

#define PI_EXTERN 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#define SPEED 2

fpp_camera :: fpp_camera(double horizontal_ang, double vertical_ang) {

    this -> horizontal_ang = horizontal_ang;
    this -> vertical_ang = vertical_ang;
    view_radius = 1;

    look_at_x = 0;
    look_at_y = 1;
    look_at_z = 0;

    position_x = 0;
    position_y = 0;
    position_z = 350;
}

void fpp_camera :: set_angles(double horizontal_ang, double vertical_ang) {

    this -> vertical_ang = vertical_ang;

    if (this -> vertical_ang < 0) this -> vertical_ang = 0;
    else if (this -> vertical_ang > 180) this -> vertical_ang = 180;

    this -> horizontal_ang = horizontal_ang;

    if (this -> horizontal_ang > 360) this -> horizontal_ang -= 360;
    else if (this -> horizontal_ang < 0) this -> horizontal_ang += 360;
}


void fpp_camera :: move_camera(bool forward, bool back, bool left, bool right, bool up, bool down) {

    // resolve directional conflicts
    if (forward && back) {
        forward = false;
        back = false;
    }
    if (left && right) {
        left = false;
        right = false;
    }
    if (up && down) {
        up = false;
        down = false;
    }
    if (!(forward || back || left || right || up || down)) return;

    double horizontal_direction_ang = 0;
    double vertical_direction_ang = 90;

    if (left) horizontal_direction_ang = (90. + back * 180) / ((forward || back) + left);
    else if (right) horizontal_direction_ang = (270. + forward * 360 + back * 180) / ((forward || back) + right);
    else horizontal_direction_ang = back * 180;
\
    if (up) vertical_direction_ang = 90 - 90. / (1 + (forward || back || left || right));
    else if (down) vertical_direction_ang = 90 + 90. / (1 + (forward || back || left || right));

    horizontal_direction_ang += horizontal_ang;

    if (horizontal_direction_ang > 360) horizontal_direction_ang -= 360;
    else if (horizontal_direction_ang < 0) horizontal_direction_ang += 360;

    position_x += SPEED * sin(vertical_direction_ang * PI_EXTERN / -180) * cos(horizontal_direction_ang * PI_EXTERN / 180);
    position_y += SPEED * sin(vertical_direction_ang * PI_EXTERN / -180) * sin(horizontal_direction_ang * PI_EXTERN / 180);
    position_z += SPEED * cos(vertical_direction_ang * PI_EXTERN /  180);
}

void fpp_camera :: set_radius(double radius) { view_radius = radius; }

// convert view angles into numerical coordinates
void fpp_camera :: look(void) {

    look_at_x = position_x + view_radius * sin(vertical_ang * PI_EXTERN / -180) * cos(horizontal_ang * PI_EXTERN / 180);
    look_at_y = position_y + view_radius * sin(vertical_ang * PI_EXTERN / -180) * sin(horizontal_ang * PI_EXTERN / 180);
    look_at_z = position_z + view_radius * cos(vertical_ang * PI_EXTERN /  180);
}
