#include "noise_layer.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

#define PGM_16_BIT 65535

void noise_layer :: initialize_heightmap(int width, int height) {

    heightmap.clear();

    for (int i = 0; i < height; i++) {
        std :: vector <float> heightmap_row;
        for (int k = 0; k < width; k++) heightmap_row.push_back(0.f);

        heightmap.push_back(heightmap_row);
    }
}


void noise_layer :: initialize_gradients(int width, int height, bool random_seed) {

    gradient_grid.clear();

    if (random_seed) srand(time(0));
    else srand(0);

    gradient gradient_vector;

    for (int i = 0; i < height; i++) {
        std :: vector <gradient> gradient_row;

        for (int k = 0; k < width; k++) {
            gradient_vector.component_x = rand() % 200 - 100.f;
            gradient_vector.component_y = rand() % 200 - 100.f;
            gradient_row.push_back(gradient_vector);
        }
        gradient_grid.push_back(gradient_row);
    }

    normalize_gradients();
}


void noise_layer :: normalize_gradients() {

    float vector_length;
    for (size_t i = 0; i < gradient_grid.size(); i++) {
        for (size_t k = 0; k < gradient_grid[i].size(); k++) {
            vector_length = sqrt(pow(gradient_grid[i][k].component_x, 2) + pow(gradient_grid[i][k].component_y, 2));
            gradient_grid[i][k].component_x /= vector_length;
            gradient_grid[i][k].component_y /= vector_length;
        }
    }
}


void noise_layer :: apply_gradients() {

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[i].size()); k++) heightmap[i][k] = perin_noise(i, k);
    }
}


float noise_layer :: perin_noise(int position_x, int position_y) {

    float point_x = (float) ((gradient_grid[0].size() - 1) / ((float) (2 * heightmap[0].size())))
                  + position_x * ((float) (gradient_grid[0].size() - 1) / (float) (heightmap[0].size()));

    float point_y = (float) ((gradient_grid.size() - 1) / ((float) (2 * heightmap.size())))
                  + position_y * ((float) (gradient_grid.size() - 1) / (float) (heightmap.size()));

    int gxi_1 = (int) floor(point_x);
    int gyi_1 = (int) floor(point_y);
    int gxi_2 = (int) ceil(point_x);
    int gyi_2 = (int) ceil(point_y);

    float dot_gradient_x1 = gradient_grid[gxi_1][gyi_1].component_x * (point_x - gxi_1) + gradient_grid[gxi_1][gyi_1].component_y * (point_y - gyi_1);
    float dot_gradient_y1 = gradient_grid[gxi_2][gyi_1].component_x * (point_x - gxi_2) + gradient_grid[gxi_2][gyi_1].component_y * (point_y - gyi_1);
    float dot_gradient_x2 = gradient_grid[gxi_1][gyi_2].component_x * (point_x - gxi_1) + gradient_grid[gxi_1][gyi_2].component_y * (point_y - gyi_2);
    float dot_gradient_y2 = gradient_grid[gxi_2][gyi_2].component_x * (point_x - gxi_2) + gradient_grid[gxi_2][gyi_2].component_y * (point_y - gyi_2);

    return (smoothstep_interpolation(
            smoothstep_interpolation(dot_gradient_x1, dot_gradient_y1, point_x - gxi_1),
            smoothstep_interpolation(dot_gradient_x2, dot_gradient_y2, point_x - gxi_1),
            point_y - gyi_1));
}


float noise_layer :: smoothstep_interpolation(float vec_1, float vec_2, float weight) {

    if (weight < 0) return vec_1;
    if (weight > 1) return vec_2;

    return (vec_2 - vec_1) * ((weight * (weight * 6 - 15) + 10) * weight * weight * weight) + vec_1;
}


void noise_layer :: normalize_heightmap(int amp) {

    float min = 0;
    float max = 0;

//    for (int i = 0; i < heightmap.size(); i++) {
//        for (int k = 0; k < heightmap[i].size(); k++) {
//            std :: cout << heightmap[i][k] << "val\n";
//        }
//    }

//    for (int i = 0; i < heightmap.size(); i++) {
//        for (int k = 0; k < heightmap[i].size(); k++) {
//            if (heightmap[i][k] > max) max = heightmap[i][k];
//            if (heightmap[i][k] < min) min = heightmap[i][k];
//        }
//    }

//    std :: cout << "min and max" << min << "  " << max << "\n";

    for (int i = 0; i < heightmap.size(); i++) {
        for (int k = 0; k < heightmap[i].size(); k++) {
            heightmap[i][k] *= 10000;
            heightmap[i][k] *= ((float) amp / 100.f);
            if (heightmap[i][k] > max) max = heightmap[i][k];
            if (heightmap[i][k] < min) min = heightmap[i][k];
//            heightmap[i][k] += -min;
//            heightmap[i][k] *= 10000;
           // heightmap[i][k] = floor(heightmap[i][k]);


//            heightmap[i][k] *=
//            if (heightmap[i][k] > max) max = heightmap[i][k];
//            if (heightmap[i][k] < min) min = heightmap[i][k];
        }
    }

//    for (int i = 0; i < heightmap.size(); i++) {
//        for (int k = 0; k < heightmap[i].size(); k++) {
//            if (heightmap[i][k] > max) max = heightmap[i][k];
//            if (heightmap[i][k] < min) min = heightmap[i][k];
//        }
//    }

    if (min < 0) {
        for (int i = 0; i < heightmap.size(); i++) {
            for (int k = 0; k < heightmap[i].size(); k++) heightmap[i][k] += -min;
        }
    }




//    std :: cout << "mac" << ((max - min) * 50) << "\n";
}

void noise_layer :: create_layer(int tn_size_x, int tn_size_y, int gg_size_x, int gg_size_y, int amp, bool random) {

    initialize_heightmap(tn_size_x, tn_size_y);
    initialize_gradients(gg_size_x, gg_size_y, random);
    apply_gradients();
    normalize_heightmap(amp);
}
