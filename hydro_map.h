#ifndef HYDRO_MAP_H
#define HYDRO_MAP_H

#include <vector>
#include "hydro_flux.h"
#include "hydro_velocity.h"


class hydro_map {

public:

    hydro_map(int x, int y);

    int size_x;
    int size_y;

    std :: vector <std :: vector <float> > watermap;
    std :: vector <std :: vector <float> > sedimap;

    std :: vector <std :: vector <hydro_velocity*> > velocity_field;
    std :: vector <std :: vector <hydro_flux*> > flux_field;

    float get_inflow_flux(int to_x, int to_y, int from_x, int from_y);
    float inflow_sum(int x, int y);
    void update_velocity(int x, int y, float intermediate_level, float final_level);

};

#endif // HYDRO_MAP_H
