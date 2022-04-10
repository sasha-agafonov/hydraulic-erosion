#include "hydro_velocity.h"

#include <cmath>

hydro_velocity :: hydro_velocity() {

    x = 0;
    y = 0;

}

float hydro_velocity :: magnitude() { return sqrt(pow(x, 2) + pow(y, 2)); }
