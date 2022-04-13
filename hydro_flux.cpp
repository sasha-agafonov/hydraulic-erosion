#include "hydro_flux.h"

hydro_flux :: hydro_flux() {

    up = 0;
    down = 0;
    left = 0;
    right = 0;

}


void hydro_flux :: scale(float scale) {

    up *= scale;
    down *= scale;
    left *= scale;
    right *= scale;

}


void hydro_flux :: set_zeroes() {

    up = 0;
    down = 0;
    left = 0;
    right = 0;

}


float hydro_flux :: sum() { return up + down + left + right; }
