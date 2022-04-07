#ifndef HYDRO2_H
#define HYDRO2_H

#include <vector>

typedef struct neighbour {

    int index_x;
    int index_y;

    float water_height;
    float land_height;
    float total_height;
    float sediment;

} neighbour;


class hydro2 {

public:

    hydro2();

    std :: vector <std :: vector <float> > heightmap;
    std :: vector <std :: vector <float> > bounded_heightmap;
    std :: vector <std :: vector <float> > bounded_watermap;
    std :: vector <std :: vector <float> > sediment_map;

    void load_heightmap();
    void create_bounded_heightmap();
    void create_bounded_watermap();
    void create_sediment_map();
    void output_heightmap();
    void drop();

    void distribute_water(int units);
    void erode(int steps);

};

#endif // HYDRO2_H
