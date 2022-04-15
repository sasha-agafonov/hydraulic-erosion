#ifndef HYDRO_H
#define HYDRO_H

#include <vector>

#include "hydro_map.h"
#include "hydro_flux.h"


typedef struct normal_vector {

    float x;
    float y;
    float z;

} normal_vector;


class hydro {

public:

    hydro();

    std :: vector <std :: vector <float> > heightmap;
    std :: vector <std :: vector <float> > temp_heightmap;

    hydro_map* current_map;
    hydro_map* updated_map;

    float water;
    float capacity;
    float erosion_rate;
    float deposition_rate;
    float evaporation_rate;
    float post_evaporation_rate;
    bool drops;

    hydro_flux compute_flux(int x, int y, float current_height);

    void set_parameters(float water, float capacity, float erosion_rate, float deposition_rate, float evaporation_rate, float post_evaporation_rate, bool drops);

    float get_total_height(int x, int y);
    float euler_step(float x, float y);
    float transport_capacity(int x, int y);

    void scale_flux(int x, int y, float current_height);
    void update_water_level(int x, int y);
    void erosion_deposition(int x, int y);
    void update_cell(int x, int y);
    void erode(int cycles);

    void dynamic_load();
    void dynamic_erode();
    void dynamic_evaporate();
    void dynamic_delete();

    bool is_wet();
    bool is_in_bounds(int x, int y);
    void drop(int x, int y);

    normal_vector normal(int x, int y);

    float incline_sin(normal_vector normal);
    float vector_length(float x, float y, float z);

    void load_heightmap();
    void check_heightmap();
    void output_heightmap();


};

#endif // HYDRO_H
