#include "hydro4.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#define PGM_8_BIT 255
#define PGM_16_BIT 65535
#define IF_OUT_OF_BOUNDS if (x < 0 || y < 0 || x >= static_cast <int> (heightmap.size()) || y >= static_cast <int> (heightmap[0].size()))
#define GRAVITY 9.81f
#define NORMALIZATION_FACTOR 400
#define TIME_STEP 1.f
#define FOR_EACH_CELL for (int i = 0; i < static_cast <int> (heightmap.size()); i++) { for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
#define FOR_EACH_CELL_2 for (int i = static_cast <int> (heightmap.size()) - 1; i >= 0; i--) { for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
#define END }}
#define WATER 0.001
#define CAPACITY 0.2


hydro4 :: hydro4() {


}

void hydro4 :: load_heightmap() {

    using namespace std;

    // open .pgm image
    ifstream terrain_data("../terrain/heightmap.pgm");

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

    heightmap.clear();

    for (int i = 0; i < terrain_size; i++) {

        getline(terrain_data, happy_string);

        istringstream unhappy_string_stream(happy_string);
        vector <float> pixel_row;

        while (getline(unhappy_string_stream, unhappy_string, ' ')) pixel_row.push_back(stof(unhappy_string));

        heightmap.push_back(pixel_row);
    }

}


hydro_flux hydro4 :: compute_flux(int x, int y, float current_height) {

    hydro_flux flux;

    IF_OUT_OF_BOUNDS return flux;

    if (x - 1 < 0) flux.up = 0;
    else flux.up = std :: max(0.f, current_map -> flux_field[x][y] -> up + TIME_STEP * GRAVITY * (current_height - heightmap[x - 1][y] - current_map -> watermap[x - 1][y]));

    if (y - 1 < 0) flux.left = 0;
    else flux.left = std :: max(0.f, current_map -> flux_field[x][y] -> left + TIME_STEP * GRAVITY * (current_height - heightmap[x][y - 1] - current_map -> watermap[x][y - 1]));

    if (x + 1 >= static_cast <int> (heightmap.size())) flux.down = 0;
    else flux.down = std :: max(0.f, current_map -> flux_field[x][y] -> down + TIME_STEP * GRAVITY * (current_height - heightmap[x + 1][y] - current_map -> watermap[x + 1][y]));

    if (y + 1 >= static_cast <int> (heightmap[0].size())) flux.right = 0;
    else flux.right = std :: max(0.f, current_map -> flux_field[x][y] -> right + TIME_STEP * GRAVITY * (current_height - heightmap[x][y + 1] - current_map -> watermap[x][y + 1]));

    return flux;

}


void hydro4 :: scale_flux(int x, int y, float current_height) {

    if (current_height < 0) return;

    IF_OUT_OF_BOUNDS return;

    hydro_flux flux;

    flux = compute_flux(x, y, current_height);


    if (flux.sum() <= 0) flux.set_zeroes();
    else if (flux.sum() > current_map -> watermap[x][y]) flux.scale(current_map -> watermap[x][y] / (flux.sum() * TIME_STEP));


    *(updated_map -> flux_field[x][y]) = flux;
    *(current_map -> flux_field[x][y]) = flux;

}


void hydro4 :: update_parameters(int x, int y) {

    scale_flux(x, y, heightmap[x][y] + current_map -> watermap[x][y]);

}


void hydro4 :: update_water_cell(int x, int y) {

    IF_OUT_OF_BOUNDS return;

    updated_map -> watermap[x][y] = std :: max(0.f, current_map -> watermap[x][y] + TIME_STEP * (updated_map -> inflow_sum(x, y) - updated_map -> flux_field[x][y] -> sum()));

//    heightmap[x][y] -= updated_map -> watermap[x][y] * 0.2;
//    if (updated_map -> watermap[x][y] < 0) updated_map -> watermap[x][y] = 0;

}


normal_vector hydro4 :: normal(int x, int y) {

        normal_vector normal;

        normal.x = 0;
        normal.y = 0;
        normal.z = 0;

        std :: vector <int> not_normal;

        if (!(x - 1 < 0 || x - 1 >= static_cast <int> (heightmap.size()))) {
            not_normal.push_back(x - 1);
            not_normal.push_back(y);
        }

        if (!(y - 1 < 0 || y - 1 >= static_cast <int> (heightmap[0].size()))) {
            not_normal.push_back(x);
            not_normal.push_back(y - 1);
        }

        if (!(x + 1 < 0 || x + 1 >= static_cast <int> (heightmap.size()))) {
            not_normal.push_back(x + 1);
            not_normal.push_back(y);
        }

        if (!(y + 1 < 0 || y + 1 >= static_cast <int> (heightmap[0].size()))) {
            not_normal.push_back(x);
            not_normal.push_back(y + 1);
        }

        for (int i = 0; i < static_cast <int> (not_normal.size()); i += 2) {

            float vector_vx = not_normal[i] - x;
            float vector_vy = not_normal[i + 1] - y;
            float vector_vz = heightmap[i][i + 1] - heightmap[x][y];

            float vector_ux = not_normal[(i + 2) % static_cast <int> (not_normal.size())] - x;
            float vector_uy = not_normal[(i + 3) % static_cast <int> (not_normal.size())] - y;
            float vector_uz = heightmap[(i + 2) % static_cast <int> (not_normal.size())][(i + 3) % static_cast <int> (not_normal.size())] - heightmap[x][y];

            normal.x += ((vector_vy * vector_uz) - (vector_vz * vector_uy));
            normal.y += ((vector_vz * vector_ux) - (vector_vx * vector_uz));
            normal.z += ((vector_vx * vector_uy) - (vector_vy * vector_ux));

        }

        if (static_cast <int> (not_normal.size()) > 0) {

            normal.x /= static_cast <int> (not_normal.size());
            normal.y /= static_cast <int> (not_normal.size());
            normal.z /= static_cast <int> (not_normal.size());
        }

        return normal;

}

float hydro4 :: incline(normal_vector normal) { return acos(normal.z / sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2))); }


void hydro4 :: erode(int cycles) {

    load_heightmap();

    FOR_EACH_CELL heightmap[i][k] /= NORMALIZATION_FACTOR; END

    current_map = new hydro_map(static_cast <int> (heightmap.size()), static_cast <int> (heightmap[0].size()));

    updated_map = new hydro_map(static_cast <int> (heightmap.size()), static_cast <int> (heightmap[0].size()));





    for (int cycle = 0; cycle < cycles; cycle++) {

        FOR_EACH_CELL current_map -> watermap[i][k] += WATER * TIME_STEP; END
                // compute new flux here
        FOR_EACH_CELL scale_flux(i, k, heightmap[i][k] + current_map -> watermap[i][k]); END

        FOR_EACH_CELL update_water_cell(i, k); END

        FOR_EACH_CELL current_map -> update_velocity(i, k, current_map -> watermap[i][k], updated_map -> watermap[i][k]); END

        FOR_EACH_CELL current_map -> sedimap[i][k] = CAPACITY * current_map -> velocity_field[i][k] -> magnitude() * sin(incline(normal(i, k)));    END

        *(current_map) = *(updated_map);

    }

    output_heightmap();

}


void hydro4 :: output_heightmap() {

    std :: ofstream happy_file;

    // eroded heightmap for rendering
    happy_file.open("../terrain/heightmap_eroded2_preview.pgm");
    happy_file << "P2\n";
    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
    happy_file << "65535\n";

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << (current_map -> watermap[i][k] + heightmap[i][k]) * 400 << '\n';
            else happy_file << (current_map -> watermap[i][k] + heightmap[i][k]) * 400  << ' ';
        }
    }

    happy_file.close();

    happy_file.open("../terrain/waterters.pgm");
    happy_file << "P2\n";
    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
    happy_file << "65535\n";

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << current_map -> watermap[i][k] * 400<< '\n';
            else happy_file << current_map -> watermap[i][k] * 400 << ' ';
        }
    }

    happy_file.close();

}
