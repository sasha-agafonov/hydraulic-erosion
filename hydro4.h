#ifndef HYDRO4_H
#define HYDRO4_H

#include <vector>

#include "hydro_map.h"
#include "hydro_flux.h"

typedef struct normal_vector {

    float x;
    float y;
    float z;

} normal_vector;


class hydro4 {

public:

    hydro4();

    std :: vector <std :: vector <float> > heightmap;
    std :: vector <std :: vector <float> > temp_heightmap;

    hydro_map* current_map;
    hydro_map* updated_map;

    void erode(int cycles);

    int cyc;
    bool rain;

    void load_heightmap();
    void output_heightmap();

    void update_parameters(int x, int y);
    void update_water(int x, int y);
    void update_water_cell(int x, int y);

    float get_total_height(int x, int y);

    hydro_flux compute_flux(int x, int y, float current_height);


    void scale_flux(int x, int y, float current_height);

    void erosion_deposition(int x, int y);

    void update_cell(int x, int y);

    float euler_step(float x, float y);

    void test_1();
    void test_2();
    void test_3();

    bool is_wet();


    normal_vector normal(int x, int y);
    float incline_sin(normal_vector normal);
    float vector_length(float x, float y, float z);

    float transport_capacity(int x, int y);

};

#endif // HYDRO4_H
