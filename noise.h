#ifndef NOISE_H
#define NOISE_H

#include <QObject>
#include <vector>

typedef struct gradient_vector {

    float component_x;
    float component_y;
//    float component_z;

} gradient_vector;

typedef struct sample_point {

    float position_x;
    float position_y;
    float position_z;
//    float component_z;

} sample_point;


class noise {

public:

    noise();
    void black_noise();
    void create_vector_grid(int height, int width);
    void normalize_gradients();
    void map_samples(int height, int width);
    void interpolate();
    float dot_product(float ivec_x, float ivec_y, int gvec_x, int gvec_y);
    void create_heightmap();
    void create_preview_heightmap();
    void perlin_noise();
    void map_samples2(int height, int width);

    void create_map();

    void create_heightmap2();

    float dot_product2(float gvec_x, float gvec_y, float svec_x, float svec_y);


    float perlin_noise2(int index_x, int index_y);

    float linear_interpolation(float point_1, float point_2, float weight);
    float cubic_interpolation();
    float smoothstep_interpolation(float point_1, float point_2, float weight);

    std :: vector < std :: vector <gradient_vector> > vector_grid;

    std :: vector < std :: vector <sample_point> > sample_grid;


    std :: vector < std :: vector <float> > sample_grid2;

};

#endif // NOISE_H
