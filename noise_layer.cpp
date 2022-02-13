#include "noise_layer.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

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
    else srand(time(0));

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
        for (int k = 0; k < static_cast <int> (heightmap[i].size()); k++) {
            heightmap[i][k] = perin_noise(i, k);
        }
    }
}


float noise_layer :: perin_noise(int position_x, int position_y) {

    float point_x = (float) ((gradient_grid[0].size() - 1) / ((float) (2 * heightmap[0].size())))
                  + position_x * ((float) (gradient_grid[0].size() - 1) / (float) (heightmap[0].size()));

    float point_y = (float) ((gradient_grid.size() - 1) / ((float) (2 * heightmap.size())))
                  + position_y * ((float) (gradient_grid.size() - 1) / (float) (heightmap.size()));

//    std :: cout << point_x << "<<<<pointx\n";
//    std :: cout << point_y << "<<<<pointY\n";

    int gxi_1 = (int) floor(point_x);
    int gyi_1 = (int) floor(point_y);
    int gxi_2 = (int) ceil(point_x);
    int gyi_2 = (int) ceil(point_y);


//        std :: cout << point_x << "<<<<pointx\n";
//        std :: cout << point_y << "<<<<pointY\n";


//            std :: cout << gxi_1 << "<<<<gxi_1\n";
//            std :: cout << gyi_1 << "<<<<gyi_1\n";
//            std :: cout << gxi_2 << "<<<<gxi_2\n";
//            std :: cout << gyi_2 << "<<<<gyi_2\n";
//dot_product(gradient_grid[gxi_2][gyi_1].component_x, gradient_grid[gxi_2][gyi_1].component_y, point_x - gxi_2, point_y - gyi_1);

    float dot_gradient_x1 = dot_product(gradient_grid[gxi_1][gyi_1].component_x, gradient_grid[gxi_1][gyi_1].component_y, point_x - gxi_1, point_y - gyi_1);
    float dot_gradient_y1 = dot_product(gradient_grid[gxi_2][gyi_1].component_x, gradient_grid[gxi_2][gyi_1].component_y, point_x - gxi_2, point_y - gyi_1);
    float dot_gradient_x2 = dot_product(gradient_grid[gxi_1][gyi_2].component_x, gradient_grid[gxi_1][gyi_2].component_y, point_x - gxi_1, point_y - gyi_2);
    float dot_gradient_y2 = dot_product(gradient_grid[gxi_2][gyi_2].component_x, gradient_grid[gxi_2][gyi_2].component_y, point_x - gxi_2, point_y - gyi_2);

    return (smoothstep_interpolation(
            smoothstep_interpolation(dot_gradient_x1, dot_gradient_y1, point_x - gxi_1),
            smoothstep_interpolation(dot_gradient_x2, dot_gradient_y2, point_x - gxi_1),
            point_y - gyi_1));
}


float noise_layer :: dot_product(float gvec_x, float gvec_y, float dvec_x, float dvec_y) {

    return (gvec_x * dvec_x + gvec_y * dvec_y);

}


float noise_layer :: smoothstep_interpolation(float vec_1, float vec_2, float weight) {

    if (weight < 0) return vec_1;
    if (weight > 1) return vec_2;

    return (vec_2 - vec_1) * ((weight * (weight * 6 - 15) + 10) * weight * weight * weight) + vec_1;
}

//void noise_layer :: create_heightmap() {

//    normalize_heightmap();

//    std :: ofstream happy_file;
//    happy_file.open("../terrain/heightmap2.pgm");
//    happy_file << "P2\n";
//    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
//    happy_file << "255\n";

//    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
//        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
//            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << heightmap[i][k] << '\n';
//            else happy_file << heightmap[i][k] << ' ';
//        }
//    }
//    happy_file.close();
//}


void noise_layer :: normalize_heightmap(int amp) {

    float min = 0;
    float max = 0;

    for (int i = 0; i < heightmap.size(); i++) {
        for (int k = 0; k < heightmap[i].size(); k++) {
            if (heightmap[i][k] > max) max = heightmap[i][k];
            if (heightmap[i][k] < min) min = heightmap[i][k];
        }
    }

    for (int i = 0; i < heightmap.size(); i++) {
        for (int k = 0; k < heightmap[i].size(); k++) {
            heightmap[i][k] += -min;
            heightmap[i][k] *= 40;
            heightmap[i][k] = floor(heightmap[i][k]);


//            heightmap[i][k] *=
//            if (heightmap[i][k] > max) max = heightmap[i][k];
//            if (heightmap[i][k] < min) min = heightmap[i][k];
        }
    }

    std :: cout << "mac" << ((max - min) * 50) << "\n";
}

void noise_layer :: create_layer(int tn_size_x, int tn_size_y, int gg_size_x, int gg_size_y, int amp) {

    initialize_heightmap(tn_size_x, tn_size_y);
    initialize_gradients(gg_size_x, gg_size_y, false);
    apply_gradients();
    normalize_heightmap(amp);
}
