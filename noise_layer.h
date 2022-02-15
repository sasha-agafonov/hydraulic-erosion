#ifndef NOISE_LAYER_H
#define NOISE_LAYER_H

#include <vector>


typedef struct gradient {

    float component_x;
    float component_y;

} gradient;


class noise_layer {

public:

    void create_layer(int tn_size_x, int tn_size_y, int gg_size_x, int gg_size_y, int amp, bool random);

    void initialize_heightmap(int width, int height);
    void create_heightmap();
    void normalize_heightmap(int amp);

    void initialize_gradients(int width, int height, bool random_seed);
    void normalize_gradients();
    void apply_gradients();

    float perin_noise(int position_x, int position_y);
    float dot_product(float gvec_x, float gvec_y, float dvec_x, float dvec_y);
    float smoothstep_interpolation(float vec_1, float vec_2, float weight);

    std :: vector <std :: vector <float> > heightmap;
    std :: vector <std :: vector <gradient> > gradient_grid;
};

#endif // NOISE_LAYER_H
