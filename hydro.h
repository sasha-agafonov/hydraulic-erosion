#ifndef HYDRO_H
#define HYDRO_H

#include <vector>

typedef struct tile {

    float terrain_height;
    float water_height;
    float sediment_amount;
    int flux;

} tile;

typedef struct surrace_normal {

    float x;
    float y;
    float z;
    int height;

} surface_normal;


class hydro {

public:

    hydro();

    std :: vector <std :: vector <float> > heightmap;
    std :: vector <std :: vector <float> > bounded_heightmap;
    std :: vector <std :: vector <float> > watermap;

    void initialize_heightmap(int wx, int wy);










    void erode(int cycles);
    void spawn_rain();
    void initialize_water_map();
    void spawn_drop();


    void load_heightmap();
    void load_surface_normals();
    void load_tiles();
    void test_water();
    void accumulate();
    void flow();

    void normalize_w_levels();

    void erode_step();

    void erode();

    void rain();
    void rain_drop(int pos_x, int pos_y);

    void vec_norm(int x, int y);

    void normalize_heightmap();
    void write_heightmap();

    std :: vector <std ::vector <surface_normal> > surface_normals;

    std :: vector <std :: vector <tile> > tiles;


    std :: vector <std :: vector <float> > water_map;
    std :: vector <std :: vector <float> > sediment_map;


};

#endif // HYDRO_H
