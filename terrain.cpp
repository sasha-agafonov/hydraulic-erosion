#define GL_GLEXT_PROTOTYPES

//#include <GL/GL.h>
#include <GL/glu.h>

#include "terrain.h"

#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#define PGM_8_BIT 255
#define PGM_16_BIT 65535
#define PI_EXTERN 3.141592653589793238462643383279502884197169399375105820974944592307816406286


terrain :: terrain() : terrain_size(0) {

    triangles_count = 0;
//    water = new hydro();
    hydraulic_erosion = new hydro();

    hydraulic_erosion -> dynamic_load();
    terrain_numerical_mx = hydraulic_erosion -> heightmap;
    terrain_numerical_mx_raw = hydraulic_erosion -> heightmap;

    cycles = 0;
    current_cycle = 0;

    dynamic = true;
    eroded = false;
    loaded = false;
}


// loads a heightmap that is to be rendered
void terrain :: load_heightmap() {

    using namespace std;

    // open .pgm image

    ifstream terrain_data;


    if (eroded) terrain_data.open("../terrain/heightmap_eroded.pgm");
    else terrain_data.open("../terrain/heightmap.pgm");

    // or don't
    if (terrain_data.fail()) return;

    int terrain_size = 0;
    string happy_string, unhappy_string, str;
    istringstream happy_string_stream;

    // image file checks
    for (int i = 0; i < 3; i++) {

        getline(terrain_data, happy_string);

        // check P2 header
        if (i == 0 && happy_string.compare("P2") != 0) return;

        // get terrain dimensions
        else if (i == 1) terrain_size = stoi(happy_string.substr(0, happy_string.find(' ')));

        // accept 8-bit or 16-bit pgm only.
        else if (i == 2 && stoi(happy_string) != PGM_8_BIT && stoi(happy_string) != PGM_16_BIT) return;
    }

    terrain_numerical_mx.clear();

    for (int i = 0; i < terrain_size; i++) {

        getline(terrain_data, happy_string);

        istringstream unhappy_string_stream(happy_string);
        vector <float> pixel_row;

        while (getline(unhappy_string_stream, unhappy_string, ' ')) pixel_row.push_back(stof(unhappy_string));

        terrain_numerical_mx.push_back(pixel_row);
    }

}

// split the heightmap into triangles
void terrain :: load_triangles() {

//    v1--------v4
//    | ⟍       |
//    |   ⟍  t2 |
//    | t1  ⟍   |
//    |       ⟍ |
//    v2--------v3

    terrain_triangle_mx.clear();
    terrain_triangle_mx_original.clear();
    terrain_smooth_triangle_mx.clear();

    triangle happy_triangle_1, happy_triangle_2;
    vertex happy_vertex_1, happy_vertex_2;
    vertex happy_vertex_3, happy_vertex_4;


    for (int row = 0; row < static_cast <int> (terrain_numerical_mx.size() - 1); row++) {

        std :: vector <triangle> triangle_row;

        for (int col = 0; col < static_cast <int> (terrain_numerical_mx[0].size() - 1); col++) {

            happy_vertex_1.position_x = col;
            happy_vertex_1.position_y = row;
            happy_vertex_1.position_z = terrain_numerical_mx[row][col];

            happy_vertex_2.position_x = col;
            happy_vertex_2.position_y = row + 1;
            happy_vertex_2.position_z = terrain_numerical_mx[row + 1][col];

            happy_vertex_3.position_x = col + 1;
            happy_vertex_3.position_y = row + 1;
            happy_vertex_3.position_z = terrain_numerical_mx[row + 1][col + 1];

            happy_vertex_4.position_x = col + 1;
            happy_vertex_4.position_y = row;
            happy_vertex_4.position_z = terrain_numerical_mx[row][col + 1];

            happy_triangle_2.vertex_1 = happy_vertex_1;
            happy_triangle_1.vertex_1 = happy_vertex_1;

            happy_triangle_2.vertex_2 = happy_vertex_4;
            happy_triangle_1.vertex_2 = happy_vertex_3;

            happy_triangle_2.vertex_3 = happy_vertex_3;
            happy_triangle_1.vertex_3 = happy_vertex_2;

            triangle_row.push_back(happy_triangle_1);
            triangle_row.push_back(happy_triangle_2);

        }

        terrain_triangle_mx.push_back(triangle_row);
        terrain_smooth_triangle_mx.push_back(triangle_row);

    }

    if (dynamic) {

        for (int row = 0; row < static_cast <int> (terrain_numerical_mx_raw.size() - 1); row++) {

            std :: vector <triangle> triangle_row_original;

            for (int col = 0; col < static_cast <int> (terrain_numerical_mx_raw[0].size() - 1); col++) {

                happy_vertex_1.position_x = col;
                happy_vertex_1.position_y = row;
                happy_vertex_1.position_z = terrain_numerical_mx_raw[row][col];

                happy_vertex_2.position_x = col;
                happy_vertex_2.position_y = row + 1;
                happy_vertex_2.position_z = terrain_numerical_mx_raw[row + 1][col];

                happy_vertex_3.position_x = col + 1;
                happy_vertex_3.position_y = row + 1;
                happy_vertex_3.position_z = terrain_numerical_mx_raw[row + 1][col + 1];

                happy_vertex_4.position_x = col + 1;
                happy_vertex_4.position_y = row;
                happy_vertex_4.position_z = terrain_numerical_mx_raw[row][col + 1];

                happy_triangle_2.vertex_1 = happy_vertex_1;
                happy_triangle_1.vertex_1 = happy_vertex_1;

                happy_triangle_2.vertex_2 = happy_vertex_4;
                happy_triangle_1.vertex_2 = happy_vertex_3;

                happy_triangle_2.vertex_3 = happy_vertex_3;
                happy_triangle_1.vertex_3 = happy_vertex_2;

                triangle_row_original.push_back(happy_triangle_1);
                triangle_row_original.push_back(happy_triangle_2);

            }

            terrain_triangle_mx_original.push_back(triangle_row_original);
        }
    }
}


// compute smooth normals
void terrain :: load_smooth_normals() {
    for (int row = 0; row < static_cast <int> (terrain_smooth_triangle_mx.size()); row++) {
        for (int col = 0; col < static_cast <int> (terrain_smooth_triangle_mx[0].size()); col++) {
            if ((row <= 1|| col <= 1) || (row >= static_cast <int> (terrain_smooth_triangle_mx.size()) - 2 || col >= static_cast <int> (terrain_smooth_triangle_mx[0].size()) - 2)) {

            } else {
                if (col % 2 == 0) {
                    terrain_smooth_triangle_mx[row][col].vertex_1.normal_x = ((terrain_triangle_mx[row - 1][col].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row - 1][col - 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row - 1][col - 2].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col + 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_x)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_1.normal_y = ((terrain_triangle_mx[row - 1][col].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row - 1][col - 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row - 1][col - 2].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col + 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_y)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_1.normal_z = ((terrain_triangle_mx[row - 1][col].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row - 1][col - 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row - 1][col - 2].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col + 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_z)
                                                                           / 6.f);


                    terrain_smooth_triangle_mx[row][col].vertex_2.normal_x = ((terrain_triangle_mx[row][col + 2].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col + 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row + 1][col + 3].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row + 1][col + 2].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row + 1][col + 1].vertex_1.normal_x)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_2.normal_y = ((terrain_triangle_mx[row][col + 2].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col + 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row + 1][col + 3].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row + 1][col + 2].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row + 1][col + 1].vertex_1.normal_y)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_2.normal_z = ((terrain_triangle_mx[row][col + 2].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col + 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row + 1][col + 3].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row + 1][col + 2].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row + 1][col + 1].vertex_1.normal_z)
                                                                           / 6.f);


                    terrain_smooth_triangle_mx[row][col].vertex_3.normal_x = ((terrain_triangle_mx[row][col].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col - 2].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row + 1][col + 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row + 1][col].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row + 1][col - 1].vertex_1.normal_x)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_3.normal_y = ((terrain_triangle_mx[row][col].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col - 2].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row + 1][col + 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row + 1][col].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row + 1][col - 1].vertex_1.normal_y)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_3.normal_z = ((terrain_triangle_mx[row][col].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col - 2].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row + 1][col + 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row + 1][col].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row + 1][col - 1].vertex_1.normal_z)
                                                                           / 6.f);

                } else {

                    terrain_smooth_triangle_mx[row][col].vertex_1.normal_x = ((terrain_triangle_mx[row - 1][col - 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row - 1][col - 2].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row - 1][col - 3].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col - 2].vertex_1.normal_x)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_1.normal_y = ((terrain_triangle_mx[row - 1][col - 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row - 1][col - 2].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row - 1][col - 3].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col - 2].vertex_1.normal_y)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_1.normal_z = ((terrain_triangle_mx[row - 1][col - 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row - 1][col - 2].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row - 1][col - 3].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col - 2].vertex_1.normal_z)
                                                                           / 6.f);


                    terrain_smooth_triangle_mx[row][col].vertex_2.normal_x = ((terrain_triangle_mx[row - 1][col + 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row - 1][col].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row - 1][col - 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col + 2].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col + 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_x)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_2.normal_y = ((terrain_triangle_mx[row - 1][col + 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row - 1][col].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row - 1][col - 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col + 2].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col + 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_y)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_2.normal_z = ((terrain_triangle_mx[row - 1][col + 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row - 1][col].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row - 1][col - 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col + 2].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col + 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_z)
                                                                           / 6.f);


                    terrain_smooth_triangle_mx[row][col].vertex_3.normal_x = ((terrain_triangle_mx[row][col + 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row + 1][col].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row + 1][col + 1].vertex_1.normal_x
                                                                           + terrain_triangle_mx[row + 1][col + 2].vertex_1.normal_x)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_3.normal_y = ((terrain_triangle_mx[row][col + 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row + 1][col].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row + 1][col + 1].vertex_1.normal_y
                                                                           + terrain_triangle_mx[row + 1][col + 2].vertex_1.normal_y)
                                                                           / 6.f);

                    terrain_smooth_triangle_mx[row][col].vertex_3.normal_z = ((terrain_triangle_mx[row][col + 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row][col - 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row + 1][col].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row + 1][col + 1].vertex_1.normal_z
                                                                           + terrain_triangle_mx[row + 1][col + 2].vertex_1.normal_z)
                                                                           / 6.f);

                }
            }
        }
    }
}


// compute flat normals
void terrain :: load_normals() {

    triangle happy_triangle;

    for (int row = 0; row < static_cast <int> (terrain_triangle_mx.size()); row++) {

        for (int col = 0; col < static_cast <int> (terrain_triangle_mx[0].size()); col++) {

            happy_triangle = terrain_triangle_mx[row][col];

            happy_triangle.vertex_1.normal_x = (happy_triangle.vertex_2.position_y - happy_triangle.vertex_1.position_y)
                                             * (happy_triangle.vertex_3.position_z - happy_triangle.vertex_1.position_z)
                                             - (happy_triangle.vertex_2.position_z - happy_triangle.vertex_1.position_z)
                                             * (happy_triangle.vertex_3.position_y - happy_triangle.vertex_1.position_y);

            happy_triangle.vertex_1.normal_y = (happy_triangle.vertex_2.position_z - happy_triangle.vertex_1.position_z)
                                             * (happy_triangle.vertex_3.position_x - happy_triangle.vertex_1.position_x)
                                             - (happy_triangle.vertex_2.position_x - happy_triangle.vertex_1.position_x)
                                             * (happy_triangle.vertex_3.position_z - happy_triangle.vertex_1.position_z);

            happy_triangle.vertex_1.normal_z = (happy_triangle.vertex_2.position_x - happy_triangle.vertex_1.position_x)
                                             * (happy_triangle.vertex_3.position_y - happy_triangle.vertex_1.position_y)
                                             - (happy_triangle.vertex_2.position_y - happy_triangle.vertex_1.position_y)
                                             * (happy_triangle.vertex_3.position_x - happy_triangle.vertex_1.position_x);

            happy_triangle.vertex_2.normal_x = (happy_triangle.vertex_2.position_y - happy_triangle.vertex_1.position_y)
                                             * (happy_triangle.vertex_3.position_z - happy_triangle.vertex_1.position_z)
                                             - (happy_triangle.vertex_2.position_z - happy_triangle.vertex_1.position_z)
                                             * (happy_triangle.vertex_3.position_y - happy_triangle.vertex_1.position_y);

            happy_triangle.vertex_2.normal_y = (happy_triangle.vertex_2.position_z - happy_triangle.vertex_1.position_z)
                                             * (happy_triangle.vertex_3.position_x - happy_triangle.vertex_1.position_x)
                                             - (happy_triangle.vertex_2.position_x - happy_triangle.vertex_1.position_x)
                                             * (happy_triangle.vertex_3.position_z - happy_triangle.vertex_1.position_z);

            happy_triangle.vertex_2.normal_z = (happy_triangle.vertex_2.position_x - happy_triangle.vertex_1.position_x)
                                             * (happy_triangle.vertex_3.position_y - happy_triangle.vertex_1.position_y)
                                             - (happy_triangle.vertex_2.position_y - happy_triangle.vertex_1.position_y)
                                             * (happy_triangle.vertex_3.position_x - happy_triangle.vertex_1.position_x);

            happy_triangle.vertex_3.normal_x = (happy_triangle.vertex_2.position_y - happy_triangle.vertex_1.position_y)
                                             * (happy_triangle.vertex_3.position_z - happy_triangle.vertex_1.position_z)
                                             - (happy_triangle.vertex_2.position_z - happy_triangle.vertex_1.position_z)
                                             * (happy_triangle.vertex_3.position_y - happy_triangle.vertex_1.position_y);

            happy_triangle.vertex_3.normal_y = (happy_triangle.vertex_2.position_z - happy_triangle.vertex_1.position_z)
                                             * (happy_triangle.vertex_3.position_x - happy_triangle.vertex_1.position_x)
                                             - (happy_triangle.vertex_2.position_x - happy_triangle.vertex_1.position_x)
                                             * (happy_triangle.vertex_3.position_z - happy_triangle.vertex_1.position_z);

            happy_triangle.vertex_3.normal_z = (happy_triangle.vertex_2.position_x - happy_triangle.vertex_1.position_x)
                                             * (happy_triangle.vertex_3.position_y - happy_triangle.vertex_1.position_y)
                                             - (happy_triangle.vertex_2.position_y - happy_triangle.vertex_1.position_y)
                                             * (happy_triangle.vertex_3.position_x - happy_triangle.vertex_1.position_x);

            terrain_triangle_mx[row][col] = happy_triangle;
        }
    }
}


// terrain :: color_interpolate() {

//}
// compute vertex colors
void terrain :: load_colors() {

    terrain_colors.clear();
    minimax();

    float color_1 = 0;
    float color_2 = 0;
    float color_3 = 0;

    float water;

    for (int i = 2; i < terrain_triangle_mx.size() - 2; i++) {

        for (int x = 2; x < terrain_triangle_mx[0].size() - 2; x++) {

            color_1 = (0.725 - 0.227) * terrain_triangle_mx[i][x].vertex_1.position_z / (max - min) + 0.227;
            color_2 = (0.662 - 0.552) * terrain_triangle_mx[i][x].vertex_1.position_z / (max - min) + 0.552;
            color_3 = (0.592 - 0.321) * terrain_triangle_mx[i][x].vertex_1.position_z / (max - min) + 0.321;

            if (dynamic) {

                water = fabs(terrain_triangle_mx[i][x].vertex_1.position_z - terrain_triangle_mx_original[i][x].vertex_1.position_z) / 2;

               // std :: cout << terrain_triangle_mx_original[i][x].vertex_1.position_z << "\n";

                color_1 = (0.149f - color_1) * std :: min(1.f, water) + color_1;
                color_2 = (0.533f - color_2) * std :: min(1.f, water) + color_2;
                color_3 = (0.772f - color_3) * std :: min(1.f, water) + color_3;

                color_1 = (0.121f - color_1) * std :: min(1.f, water / 8) + color_1;
                color_2 = (0.243f - color_2) * std :: min(1.f, water / 8) + color_2;
                color_3 = (0.556f - color_3) * std :: min(1.f, water / 8) + color_3;

            }

            terrain_colors.push_back(color_1);
            terrain_colors.push_back(color_2);
            terrain_colors.push_back(color_3);

            color_1 = (0.725 - 0.227) * terrain_triangle_mx[i][x].vertex_2.position_z / (max - min) + 0.227;
            color_2 = (0.662 - 0.552) * terrain_triangle_mx[i][x].vertex_2.position_z / (max - min) + 0.552;
            color_3 = (0.592 - 0.321) * terrain_triangle_mx[i][x].vertex_2.position_z / (max - min) + 0.321;

            if (dynamic) {

                water = fabs(terrain_triangle_mx[i][x].vertex_2.position_z - terrain_triangle_mx_original[i][x].vertex_2.position_z) / 2;

                color_1 = (0.149f - color_1) * std :: min(1.f, water) + color_1;
                color_2 = (0.533f - color_2) * std :: min(1.f, water) + color_2;
                color_3 = (0.772f - color_3) * std :: min(1.f, water) + color_3;

                color_1 = (0.121f - color_1) * std :: min(1.f, water / 8) + color_1;
                color_2 = (0.243f - color_2) * std :: min(1.f, water / 8) + color_2;
                color_3 = (0.556f - color_3) * std :: min(1.f, water / 8) + color_3;

            }

            terrain_colors.push_back(color_1);
            terrain_colors.push_back(color_2);
            terrain_colors.push_back(color_3);

            color_1 = (0.725 - 0.227) * terrain_triangle_mx[i][x].vertex_3.position_z / (max - min) + 0.227;
            color_2 = (0.662 - 0.552) * terrain_triangle_mx[i][x].vertex_3.position_z / (max - min) + 0.552;
            color_3 = (0.592 - 0.321) * terrain_triangle_mx[i][x].vertex_3.position_z / (max - min) + 0.321;

            if (dynamic) {

                water = fabs(terrain_triangle_mx[i][x].vertex_3.position_z - terrain_triangle_mx_original[i][x].vertex_3.position_z) / 2;

                color_1 = (0.149f - color_1) * std :: min(1.f, water) + color_1;
                color_2 = (0.533f - color_2) * std :: min(1.f, water) + color_2;
                color_3 = (0.772f - color_3) * std :: min(1.f, water) + color_3;

                color_1 = (0.121f - color_1) * std :: min(1.f, water / 8) + color_1;
                color_2 = (0.243f - color_2) * std :: min(1.f, water / 8) + color_2;
                color_3 = (0.556f - color_3) * std :: min(1.f, water / 8) + color_3;

            }

            terrain_colors.push_back(color_1);
            terrain_colors.push_back(color_2);
            terrain_colors.push_back(color_3);
        }

    }

}


float terrain :: interpolate_angle(float ang) {
    if (ang >= 100) return 1.f;
    else if (ang <= 50) return 0;
    else return ((ang - 50) / 50.f);

}

// load triangle vertices into an array
void terrain :: load_arrays() {

    triangles_count = num_triangles();
    terrain_positions = new float[triangles_count * 9];
    terrain_normals = new float[triangles_count * 9];

    int counter = 0;

    for (int i = 2; i < terrain_triangle_mx.size() - 2; i++) {

        for (int k = 2; k < terrain_triangle_mx[i].size() - 2; k++) {

            // vx positions
            terrain_positions[counter   *   9] = terrain_triangle_mx[i][k].vertex_1.position_x;
            terrain_positions[counter * 9 + 1] = terrain_triangle_mx[i][k].vertex_1.position_y;
            terrain_positions[counter * 9 + 2] = terrain_triangle_mx[i][k].vertex_1.position_z;

            terrain_positions[counter * 9 + 3] = terrain_triangle_mx[i][k].vertex_2.position_x;
            terrain_positions[counter * 9 + 4] = terrain_triangle_mx[i][k].vertex_2.position_y;
            terrain_positions[counter * 9 + 5] = terrain_triangle_mx[i][k].vertex_2.position_z;

            terrain_positions[counter * 9 + 6] = terrain_triangle_mx[i][k].vertex_3.position_x;
            terrain_positions[counter * 9 + 7] = terrain_triangle_mx[i][k].vertex_3.position_y;
            terrain_positions[counter * 9 + 8] = terrain_triangle_mx[i][k].vertex_3.position_z;

            // vx normals
            terrain_normals[counter   *   9] = terrain_smooth_triangle_mx[i][k].vertex_1.normal_x;
            terrain_normals[counter * 9 + 1] = terrain_smooth_triangle_mx[i][k].vertex_1.normal_y;
            terrain_normals[counter * 9 + 2] = terrain_smooth_triangle_mx[i][k].vertex_1.normal_z;

            terrain_normals[counter * 9 + 3] = terrain_smooth_triangle_mx[i][k].vertex_2.normal_x;
            terrain_normals[counter * 9 + 4] = terrain_smooth_triangle_mx[i][k].vertex_2.normal_y;
            terrain_normals[counter * 9 + 5] = terrain_smooth_triangle_mx[i][k].vertex_2.normal_z;

            terrain_normals[counter * 9 + 6] = terrain_smooth_triangle_mx[i][k].vertex_3.normal_x;
            terrain_normals[counter * 9 + 7] = terrain_smooth_triangle_mx[i][k].vertex_3.normal_y;
            terrain_normals[counter * 9 + 8] = terrain_smooth_triangle_mx[i][k].vertex_3.normal_z;

            counter++;
        }
    }

}

float terrain :: normal_angle(float x, float y, float z) { return ( std :: acos( z / (vec_len(x, y, z)) * vec_len(0, 0, 1))); }

float terrain :: vec_len(float x, float y, float z) { return (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))); }



// controller
void terrain :: load_terrain() {

    load_heightmap();
    load_triangles();
    normalize_terrain(400);
    stretch_terrain(1, 1);
    load_normals();
    load_smooth_normals();
    load_arrays();
    load_colors();

}


// draw triangle by triangle, deprecated
void terrain :: draw_terrain() {

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE,   m200.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  m200.specular);
    glMaterialf( GL_FRONT, GL_SHININESS, m200.shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   m200.ambient);

    for (int row = 0; row < terrain_triangle_mx.size(); row++) {
        for (int col = 0; col < terrain_triangle_mx[0].size(); col++) {
            glBegin(GL_TRIANGLES);

            glNormal3f( terrain_triangle_mx[row][col].vertex_1.normal_x,   terrain_triangle_mx[row][col].vertex_1.normal_y,   terrain_triangle_mx[row][col].vertex_1.normal_z);
            glVertex3f( terrain_triangle_mx[row][col].vertex_1.position_x, terrain_triangle_mx[row][col].vertex_1.position_y, terrain_triangle_mx[row][col].vertex_1.position_z);


            glNormal3f( terrain_triangle_mx[row][col].vertex_2.normal_x,   terrain_triangle_mx[row][col].vertex_2.normal_y,   terrain_triangle_mx[row][col].vertex_2.normal_z);
            glVertex3f( terrain_triangle_mx[row][col].vertex_2.position_x, terrain_triangle_mx[row][col].vertex_2.position_y, terrain_triangle_mx[row][col].vertex_2.position_z);

            glNormal3f( terrain_triangle_mx[row][col].vertex_3.normal_x,   terrain_triangle_mx[row][col].vertex_3.normal_y,   terrain_triangle_mx[row][col].vertex_3.normal_z);
            glVertex3f( terrain_triangle_mx[row][col].vertex_3.position_x, terrain_triangle_mx[row][col].vertex_3.position_y, terrain_triangle_mx[row][col].vertex_3.position_z);

            glEnd();
        }
    }

    glPopMatrix();
}

void terrain :: load_hydro() {

    if (!loaded && dynamic) {

        hydraulic_erosion -> dynamic_load();
        loaded = true;
        terrain_numerical_mx = hydraulic_erosion -> heightmap;
        terrain_numerical_mx_raw = hydraulic_erosion -> heightmap;

    }

    if (dynamic) {

        free(terrain_positions);
        free(terrain_normals);

        terrain_numerical_mx = hydraulic_erosion -> heightmap;
        terrain_numerical_mx_raw = hydraulic_erosion -> heightmap;

        if (current_cycle < cycles) {

            current_cycle ++;
            hydraulic_erosion -> dynamic_erode();

            terrain_numerical_mx = hydraulic_erosion -> heightmap;
            terrain_numerical_mx_raw = hydraulic_erosion -> heightmap;

            for (int i = 0; i < hydraulic_erosion -> heightmap.size(); i++) {
                for (int k = 0; k < hydraulic_erosion -> heightmap.size(); k++) {
                    terrain_numerical_mx[i][k] += hydraulic_erosion -> updated_map -> watermap[i][k]; } }
        } else {

            hydraulic_erosion -> dynamic_evaporate();

            for (int i = 0; i < hydraulic_erosion -> heightmap.size(); i++) {
                for (int k = 0; k < hydraulic_erosion -> heightmap.size(); k++) {
                    terrain_numerical_mx[i][k] += hydraulic_erosion -> updated_map -> watermap[i][k]; } }

            if (!hydraulic_erosion -> is_wet()) {

                dynamic = false;
                current_cycle = 0;
                hydraulic_erosion -> dynamic_delete();

            }
        }

        load_triangles();
        load_normals();
        load_smooth_normals();
        load_arrays();
        load_colors();

    }
}

// draw from an array of vertices, slightly better
void terrain :: draw_terrain_arrays() {

    if (dynamic) load_hydro();

    glPushMatrix();

    glVertexPointer(3, GL_FLOAT, 0, terrain_positions);
    glColorPointer(3, GL_FLOAT, 0, terrain_colors.data());
    glNormalPointer(GL_FLOAT, 0, terrain_normals);
    glDrawArrays( GL_TRIANGLES, 0, triangles_count * 3);

    glPopMatrix();
}


void terrain :: minimax() {

    min = PGM_16_BIT;
    max = 0;

    for (int i = 0; i < static_cast <int> (terrain_triangle_mx.size()); i++) {
        for (int k = 0; k < static_cast <int> (terrain_triangle_mx[0].size()); k++) {

            if (terrain_triangle_mx[i][k].vertex_1.position_z < min) min = terrain_triangle_mx[i][k].vertex_1.position_z;
            if (terrain_triangle_mx[i][k].vertex_1.position_z > max) max = terrain_triangle_mx[i][k].vertex_1.position_z;

            if (terrain_triangle_mx[i][k].vertex_2.position_z < min) min = terrain_triangle_mx[i][k].vertex_2.position_z;
            if (terrain_triangle_mx[i][k].vertex_2.position_z > max) max = terrain_triangle_mx[i][k].vertex_2.position_z;

            if (terrain_triangle_mx[i][k].vertex_3.position_z < min) min = terrain_triangle_mx[i][k].vertex_3.position_z;
            if (terrain_triangle_mx[i][k].vertex_3.position_z > max) max = terrain_triangle_mx[i][k].vertex_1.position_z;

        }
    }
}



//void terrain :: minimax() {
//    min = terrain_numerical_mx[0][0];
//    max = terrain_numerical_mx[0][0];
//    for (int i = 0; i < terrain_numerical_mx.size(); i++) {
//        for (int k = 0; k < terrain_numerical_mx.size(); k++) {
//            if (terrain_numerical_mx[i][k] < min) min = terrain_numerical_mx[i][k];
//            if (terrain_numerical_mx[i][k] > max) max = terrain_numerical_mx[i][k];
//        }
//    }
//}

// scale the height
void terrain :: normalize_terrain(int factor) {

    for (int i = 0; i < terrain_triangle_mx.size(); i++) {
        for (int k = 0; k < terrain_triangle_mx[i].size(); k++) {
            terrain_triangle_mx[i][k].vertex_1.position_z /= factor;
            terrain_triangle_mx[i][k].vertex_2.position_z /= factor;
            terrain_triangle_mx[i][k].vertex_3.position_z /= factor;
        }
    }
}

// extrude
void terrain :: stretch_terrain(int stretch_x, int stretch_y) {

    for (int i = 0; i < terrain_triangle_mx.size(); i++) {
        for (int k = 0; k < terrain_triangle_mx[i].size(); k++) {

            terrain_triangle_mx[i][k].vertex_1.position_x *= stretch_x;
            terrain_triangle_mx[i][k].vertex_2.position_x *= stretch_x;
            terrain_triangle_mx[i][k].vertex_3.position_x *= stretch_x;

            terrain_triangle_mx[i][k].vertex_1.position_y *= stretch_y;
            terrain_triangle_mx[i][k].vertex_2.position_y *= stretch_y;
            terrain_triangle_mx[i][k].vertex_3.position_y *= stretch_y;
        }
    }
}

// counts the number of triangles in the terrain
int terrain :: num_triangles() {
    int num = 0;
    for (int i = 2; i < terrain_triangle_mx.size() - 2; i++) num += (terrain_triangle_mx[i].size() - 4);
    return num;
}


