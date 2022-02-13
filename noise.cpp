#include "noise.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

#define MAP_SIZE 1000

noise :: noise() {

}

void noise :: normalize_gradients() {
    float vector_length;
    for (size_t i = 0; i < vector_grid.size(); i++) {
        for (size_t k = 0; k < vector_grid[i].size(); k++) {
            vector_length = sqrt(pow(vector_grid[i][k].component_x, 2) + pow(vector_grid[i][k].component_y, 2));
            vector_grid[i][k].component_x /= vector_length;
            vector_grid[i][k].component_y /= vector_length;

        }
    }
}


void noise :: create_vector_grid(int height, int width) {
    vector_grid.clear();
    gradient_vector gradient;
    srand(time(0));
    for (int i = 0; i < height; i++) {
        std :: vector <gradient_vector> vector_row;
        for (int k = 0; k < width; k++) {
            gradient.component_x = rand() % 200 - 100.f;
            gradient.component_y = rand() % 200 - 100.f;
            vector_row.push_back(gradient);
        }
        vector_grid.push_back(vector_row);
    }
}


void noise :: map_samples(int height, int width) {
    sample_grid.clear();
    sample_point sample;
    float step;
    float xval, yval = 0;

    step = (float)(vector_grid.size() - 1) / width;

    for (int i = 0; i < height; i++) {

         xval = 0;
         if (i == 0) yval += step / 2;
         else yval += step;
         std :: vector <sample_point> vector_row;

        for (int k = 0; k < width; k++) {
            if (k == 0) xval += step / 2;
            else xval += step;
            sample.position_x = xval;
            sample.position_y = yval;
            sample.position_z = 0;
            vector_row.push_back(sample);
        }
        sample_grid.push_back(vector_row);
    }

//    for (int i = 0; i < height; i++) {
//    for (int k = 0 ; k < width; k++) {
//        std :: cout << sample_grid[i][k].position_x << "xpos \n";
//            std :: cout << sample_grid[i][k].position_y << "ypos \n";
//    }
//  }
}


void noise :: map_samples2(int height, int width) {
    sample_grid2.clear();
     for (int i = 0; i < height; i++) {
          std :: vector <float> vector_row;
          for (int i = 0; i < width; i++) vector_row.push_back(0.f);
          sample_grid2.push_back(vector_row);
     }
}

void noise :: create_map() {
    for (int i = 0; i < sample_grid2.size(); i++) {
        for (int k = 0; k < sample_grid2.size(); k++) {
            sample_grid2[i][k] = perlin_noise2(i, k);
        }
    }
}

float noise :: linear_interpolation(float point_1, float point_2, float weight) {
    if (weight < 0) return point_1;
    if (weight > 1) return point_2;
    return (point_2 - point_1) * weight + point_1;
}

float noise :: smoothstep_interpolation(float point_1, float point_2, float weight) {
    if (weight < 0) return point_1;
    if (weight > 1) return point_2;
    return (point_2 - point_1) * ((weight * (weight * 6 - 15) + 10) * weight * weight * weight) + point_1;
}


float noise :: dot_product(float ivec_x, float ivec_y, int gvec_x, int gvec_y) {
    return ((ivec_x - gvec_x) * vector_grid[gvec_y][gvec_x].component_x + (ivec_y - gvec_y) * vector_grid[gvec_y][gvec_x].component_y);
}


float noise :: dot_product2(float gvec_x, float gvec_y, float svec_x, float svec_y) { return (gvec_x * svec_x + gvec_y * svec_y); }


float noise :: perlin_noise2(int index_x, int index_y) {

    // map point to gradient grid using its index
    float point_x = (float) ((vector_grid[0].size() - 1) / ((float) (2 * sample_grid[0].size()))) + index_x * ((float) (vector_grid[0].size() - 1) / (float) (sample_grid[0].size()));
    float point_y = (float) ((vector_grid.size()    - 1) / ((float) (2 * sample_grid.size())))    + index_y * ((float) (vector_grid.size()    - 1) / (float) (sample_grid.size()));

    // nearby gradients
    int ginx_x1 = (int) floor(point_x);
    int ginx_y1 = (int) floor(point_y);
    int ginx_x2 = (int) ceil(point_x);
    int ginx_y2 = (int) ceil(point_y);

    // dot product of distance and gradient vectors
    float dot_gradient_x1 = dot_product(vector_grid[ginx_x1][ginx_y1].component_x, vector_grid[ginx_x1][ginx_y1].component_y, point_x - ginx_x1, point_y - ginx_y1);
    float dot_gradient_y1 = dot_product(vector_grid[ginx_x1][ginx_y2].component_x, vector_grid[ginx_x1][ginx_y2].component_y, point_x - ginx_x1, point_y - ginx_y2);
    float dot_gradient_x2 = dot_product(vector_grid[ginx_x2][ginx_y1].component_x, vector_grid[ginx_x2][ginx_y1].component_y, point_x - ginx_x2, point_y - ginx_y1);
    float dot_gradient_y2 = dot_product(vector_grid[ginx_x2][ginx_y2].component_x, vector_grid[ginx_x2][ginx_y2].component_y, point_x - ginx_x2, point_y - ginx_y2);

    // interpolate the point
    return (linear_interpolation(
            linear_interpolation(dot_gradient_x1, dot_gradient_y1, point_x - ginx_x1),
            linear_interpolation(dot_gradient_x2, dot_gradient_y2, point_x - ginx_x1),
            point_y - ginx_y1));
}


void noise :: perlin_noise() {
    for (int i = 0; i < sample_grid.size(); i++) {
        for (int k = 0; k < sample_grid[i].size(); k++) {
            float wx = sample_grid[i][k].position_x - floor(sample_grid[i][k].position_x);
            float wy = sample_grid[i][k].position_y - floor(sample_grid[i][k].position_y);
            float dvec1 = dot_product(sample_grid[i][k].position_x, sample_grid[i][k].position_y, int(floor(sample_grid[i][k].position_x)), int(floor(sample_grid[i][k].position_y)));
            float dvec2 = dot_product(sample_grid[i][k].position_x, sample_grid[i][k].position_y, int(ceil(sample_grid[i][k].position_x)), int(floor(sample_grid[i][k].position_y)));
            float inter1 = smoothstep_interpolation(dvec1, dvec2, wx);
            float dvec3 = dot_product(sample_grid[i][k].position_x, sample_grid[i][k].position_y, int(floor(sample_grid[i][k].position_x)), int(ceil(sample_grid[i][k].position_y)));
            float dvec4 = dot_product(sample_grid[i][k].position_x, sample_grid[i][k].position_y, int(ceil(sample_grid[i][k].position_x)), int(ceil(sample_grid[i][k].position_y)));
            float inter2 = smoothstep_interpolation(dvec3 ,dvec4, wx);
            sample_grid[i][k].position_z += smoothstep_interpolation(inter1, inter2, wy);
        }
    }

    for (int i = 0; i < sample_grid.size(); i++) {
        for (int k = 0; k < sample_grid[i].size(); k++) {

//            std :: cout << sample_grid[i].size()<< "xuy \n";
            sample_grid[i][k].position_z *= 100;
            sample_grid[i][k].position_z += 100;
            sample_grid[i][k].position_z = floor(sample_grid[i][k].position_z);

//           std :: cout << sample_grid[i][k].position_z << "zpos lol xd \n";
            }
        }
}
//void noise :: interpolate() {
//    for (int i = 0 ; i < sample_grid.size(); i ++) {
//        for (int k = 0; k < sample_grid.size(); k ++) {
//            sample_grid[i][k] =
//        }
//    }
//}

void noise :: create_heightmap() {

    std :: ofstream happy_file;
    happy_file.open("../terrain/heightmap2.pgm");
    happy_file << "P2\n";
    happy_file << sample_grid.size() << ' ' << sample_grid[0].size() << '\n';
    happy_file << "255\n";

    for (int i = 0; i < sample_grid.size(); i++) {
        for (int k = 0; k < sample_grid[0].size(); k++) {
            if (k == sample_grid[0].size()- 1) happy_file << sample_grid[i][k].position_z << '\n';
            else happy_file << sample_grid[i][k].position_z << ' ';
        }
    }
    happy_file.close();
}


void noise :: create_heightmap2() {

    std :: ofstream happy_file;
    happy_file.open("../terrain/heightmap2.pgm");
    happy_file << "P2\n";
    happy_file << sample_grid2.size() << ' ' << sample_grid2[0].size() << '\n';
    happy_file << "255\n";

    for (int i = 0; i < sample_grid2.size(); i++) {
        for (int k = 0; k < sample_grid2[0].size(); k++) {
            if (k == sample_grid2[0].size()- 1) happy_file << sample_grid2[i][k] << '\n';
            else happy_file << sample_grid2[i][k] << ' ';
        }
    }
    happy_file.close();
}


void noise :: create_preview_heightmap() {
    std :: ofstream happy_file;
    happy_file.open("../terrain/heightmap_preview.ppm");
    happy_file << "P3\n";
    happy_file << sample_grid.size() << ' ' << sample_grid[0].size() << '\n';
    happy_file << "255\n";
    for (int i = 0; i < sample_grid.size(); i++) {
        for (int k = 0; k < sample_grid[0].size(); k++) {
            if (k == sample_grid[0].size()- 1) {
                happy_file << sample_grid[i][k].position_z -40<< ' ';
                happy_file << sample_grid[i][k].position_z - 40<< ' ';
                happy_file << sample_grid[i][k].position_z - 25<< '\n';
            }
            else {
                happy_file << sample_grid[i][k].position_z - 40 << ' ';
                happy_file << sample_grid[i][k].position_z - 40<< ' ';
                happy_file << sample_grid[i][k].position_z - 25 << ' ';
            }
        }
    }
    happy_file.close();
}

void noise :: black_noise() {
    std :: ofstream happy_file;
    happy_file.open("../terrain/heightmap.pgm");
    happy_file << "P2\n";
    happy_file << MAP_SIZE << ' ' << MAP_SIZE << '\n';
    happy_file << "255\n";

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int k = 0; k < MAP_SIZE; k++) {
            if (k == MAP_SIZE - 1) happy_file << rand() % 255 << '\n';
            else happy_file << rand() % 255 << ' ';
        }
    }
    happy_file.close();
}
