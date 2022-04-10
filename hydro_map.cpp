#include "hydro_map.h"

#define OUT_OF_BOUNDS -1

hydro_map :: hydro_map(int x, int y) {

    size_x = x;
    size_y = y;

    for (int i = 0; i < x; i++) {

        std :: vector <float> water;
        std :: vector <float> sediment;
        std :: vector <hydro_flux*> flux;
        std :: vector <hydro_velocity*> velocities;

        for (int k = 0; k < y; k++) {

            water.push_back(0);
            sediment.push_back(0);
            flux.push_back(new hydro_flux());
            velocities.push_back(new hydro_velocity());
        }

        watermap.push_back(water);
        sedimap.push_back(sediment);
        flux_field.push_back(flux);
        velocity_field.push_back(velocities);

    }
}



float hydro_map :: get_inflow_flux(int to_x, int to_y, int from_x, int from_y) {

    if (to_x < 0 || to_y < 0 || to_x >= size_x || to_y >= size_y ) return 0.f;

    if (from_x < 0 || from_y < 0 || from_x >= size_x || from_y >= size_y ) return 0.f;

    if (to_x < from_x) return flux_field[from_x][from_y] -> up;

    if (to_x > from_x) return flux_field[from_x][from_y] -> down;

    if (to_y < from_y) return flux_field[from_x][from_y] -> left;

    if (to_y > from_y) return flux_field[from_x][from_y] -> right;

    return 0.f;
}


float hydro_map :: inflow_sum(int x, int y) { return get_inflow_flux(x, y, x + 1, y) + get_inflow_flux(x, y, x - 1, y) + get_inflow_flux(x, y, x, y + 1) + get_inflow_flux(x, y, x, y - 1); }


void hydro_map :: update_velocity(int x, int y, float intermediate_level, float final_level) {

    float delta = (intermediate_level + final_level) / 2;

    float volume_x = get_inflow_flux(x, y, x + 1, y) - get_inflow_flux(x, y, x - 1, y) + flux_field[x][y] -> up - flux_field[x][y] -> down;
    float volume_y = get_inflow_flux(x, y, x, y - 1) - get_inflow_flux(x, y, x, y + 1) + flux_field[x][y] -> right - flux_field[x][y] -> left;

    velocity_field[x][y] -> x = 0.5 * volume_x / delta;
    velocity_field[x][y] -> y = 0.5 * volume_y / delta;
}
