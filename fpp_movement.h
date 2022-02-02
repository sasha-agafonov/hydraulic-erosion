#ifndef FPP_MOVEMENT_H
#define FPP_MOVEMENT_H


class fpp_movement {

public:
    fpp_movement();
    void change_position(double change_x, double change_y, double change_z);
    double position_x;
    double position_y;
    double position_z;
};

#endif // FPP_MOVEMENT_H
