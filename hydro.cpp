#include "hydro.h"

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
#define GRAVITY 10.f
#define NORMALIZATION_FACTOR 400
#define TIME_STEP 0.1f
#define FOR_EACH_CELL for (int i = 0; i < static_cast <int> (heightmap.size()); i++) { for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
#define FOR_EACH_CELL_2 for (int i = static_cast <int> (heightmap.size()) - 1; i >= 0; i--) { for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
#define END }}
#define MINIMUM_EVAPORATION_THRESHOLD 0.05f

//#define water 1.f
//#define capacity 0.05f
//#define erosion_rate 0.02f
//#define deposition_rate 0.01f
//#define evaporation_rate 0.3f


//#define water 1.f
//#define capacity 0.05f
//#define PI_EXTERN 3.141592653589793238462643383279502884197169399375105820974944592307816406286
//#define erosion_rate 0.02f
//#define deposition_rate 0.01f
//#define evaporation_rate 0.3f

hydro :: hydro() {

    water = 0;
    capacity = 0;
    erosion_rate = 0;
    deposition_rate = 0;
    evaporation_rate = 0;
    post_evaporation_rate = 0;

}


void hydro :: load_heightmap() {

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
    temp_heightmap.clear();

    for (int i = 0; i < terrain_size; i++) {

        getline(terrain_data, happy_string);

        istringstream unhappy_string_stream(happy_string);

        vector <float> pixel_row;

        while (getline(unhappy_string_stream, unhappy_string, ' ')) pixel_row.push_back(stof(unhappy_string));

        vector <float> temp_row(pixel_row.size(), 0.f);

        heightmap.push_back(pixel_row);
        temp_heightmap.push_back(temp_row);
    }

}


hydro_flux hydro :: compute_flux(int x, int y, float current_height) {

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


void hydro :: scale_flux(int x, int y, float current_height) {

    if (current_height < 0) return;

    IF_OUT_OF_BOUNDS return;

    hydro_flux flux;

    flux = compute_flux(x, y, current_height);

    if (flux.sum() <= 0) flux.set_zeroes();
    else if (flux.sum() > current_map -> watermap[x][y]) flux.scale(current_map -> watermap[x][y] / (flux.sum() * TIME_STEP));

    *(updated_map -> flux_field[x][y])  = flux;
    *(current_map -> flux_field[x][y]) = flux;

}


void hydro :: update_water_level(int x, int y) {

    IF_OUT_OF_BOUNDS return;

    updated_map -> watermap[x][y] = std :: max(0.f, current_map -> watermap[x][y] + TIME_STEP * (updated_map -> inflow_sum(x, y) - updated_map -> flux_field[x][y] -> sum()));

    if (updated_map -> watermap[x][y] < 0) updated_map -> watermap[x][y] = 0;

}


normal_vector hydro :: normal(int x, int y) {

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

        if ((x + 1 > 0 && x + 1 < static_cast <int> (heightmap.size()))) {
            not_normal.push_back(x + 1);
            not_normal.push_back(y);
        }

        if ((y + 1 > 0 && y + 1 < static_cast <int> (heightmap[0].size()))) {
            not_normal.push_back(x);
            not_normal.push_back(y + 1);
        }

        int triangles = 0;

        for (int i = 0; i < static_cast <int> (not_normal.size()); i += 2) {

            if (static_cast <int> (not_normal.size()) < 8 && i == static_cast <int> (not_normal.size()) - 2) break;

            float vector_vx = not_normal[i] - x;
            float vector_vy = not_normal[i + 1] - y;
            float vector_vz = heightmap [not_normal[i]][not_normal[i + 1]] - heightmap[x][y];

            float vector_ux = not_normal[(i + 2) % static_cast <int> (not_normal.size())] - x;
            float vector_uy = not_normal[(i + 3) % static_cast <int> (not_normal.size())] - y;
            float vector_uz = heightmap [not_normal[(i + 2) % static_cast <int> (not_normal.size())]][not_normal[(i + 3) % static_cast <int> (not_normal.size())]] - heightmap[x][y];

            normal.x += ((vector_vy * vector_uz) - (vector_vz * vector_uy));
            normal.y += ((vector_vz * vector_ux) - (vector_vx * vector_uz));
            normal.z += ((vector_vx * vector_uy) - (vector_vy * vector_ux));

            triangles++;

        }

        if (triangles > 0) {
            normal.x /= triangles;
            normal.y /= triangles;
            normal.z /= triangles;
        }


        if (normal.x == 0 && normal.y == 0 && normal.x == 0) normal.z = 1;

        return normal;

}


float hydro :: incline_sin(normal_vector normal) { return std :: max(0.1f, sin(acos(normal.z / vector_length(normal.x, normal.y, normal.z) * vector_length(0, 0, 1)))); }


float hydro :: vector_length(float x, float y, float z) { return (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))); }


float hydro :: transport_capacity(int x, int y) { return capacity * incline_sin(normal(x, y)) * updated_map -> velocity_field[x][y] -> magnitude(); }


float hydro :: euler_step(float x, float y) {

    float top    = current_map -> sedimap[floor(x)][floor(y)] * (y - floor(y)) + current_map -> sedimap[floor(x)][ceil(y)] * (ceil(y) - y);
    float bottom = current_map -> sedimap[ ceil(x)][floor(y)] * (y - floor(y)) + current_map -> sedimap[ceil(x) ][ceil(y)] * (ceil(y) - y);

    return top * (x - floor(x)) + bottom * (ceil(x) - x);

}


void hydro :: erosion_deposition(int x, int y) {

    if (transport_capacity(x, y) > current_map -> sedimap[x][y]) {

        if (heightmap[x][y] <= erosion_rate * (transport_capacity(x, y) - current_map -> sedimap[x][y])) {
            current_map -> sedimap[x][y] += heightmap[x][y];
            temp_heightmap[x][y] = -heightmap[x][y];
        } else {
            temp_heightmap[x][y] = -erosion_rate * (transport_capacity(x, y) - current_map -> sedimap[x][y]);
            current_map -> sedimap[x][y] += erosion_rate * (transport_capacity(x, y) - current_map -> sedimap[x][y]);
        }

    } else {

        temp_heightmap[x][y] = deposition_rate * (current_map -> sedimap[x][y] - transport_capacity(x, y));
        current_map -> sedimap[x][y] -= deposition_rate * (current_map -> sedimap[x][y] - transport_capacity(x, y));

    }

}


void hydro :: update_cell(int x, int y) {

    current_map -> watermap[x][y] = updated_map -> watermap[x][y];
    current_map -> sedimap[x][y] = updated_map -> sedimap[x][y];

    *(current_map -> velocity_field[x][y]) = *(updated_map -> velocity_field[x][y]);
    *(current_map -> flux_field[x][y]) = *(updated_map -> flux_field[x][y]);

}

void hydro :: set_parameters(float water, float capacity, float erosion_rate, float deposition_rate, float evaporation_rate, float post_evaporation_rate) {

    this -> water = water;
    this -> capacity = capacity;
    this -> erosion_rate = erosion_rate;
    this -> deposition_rate = deposition_rate;
    this -> evaporation_rate = evaporation_rate;
    this -> post_evaporation_rate = post_evaporation_rate;

}


void hydro :: erode(int cycles) {

    load_heightmap();

    FOR_EACH_CELL heightmap[i][k] /= NORMALIZATION_FACTOR; END

    current_map = new hydro_map(static_cast <int> (heightmap.size()), static_cast <int> (heightmap[0].size()));
    updated_map = new hydro_map(static_cast <int> (heightmap.size()), static_cast <int> (heightmap[0].size()));

    for (int cycle = 0; cycle < cycles; cycle++) {

        FOR_EACH_CELL current_map -> watermap[i][k] += 0.5 * water * TIME_STEP + (0.5 * water * TIME_STEP * (rand() % 3)); END

        // compute new flux
        FOR_EACH_CELL scale_flux(i, k, heightmap[i][k] + current_map -> watermap[i][k]); END

        // update water level based on flux
        FOR_EACH_CELL update_water_level(i, k); END

        // velocity field
        FOR_EACH_CELL updated_map -> update_velocity(i, k, current_map -> watermap[i][k], updated_map -> watermap[i][k]); END

        // erosion and deposition
        FOR_EACH_CELL erosion_deposition(i, k); END

        // update sediment
        FOR_EACH_CELL heightmap[i][k] += temp_heightmap[i][k]; END

        // sediment transport
        FOR_EACH_CELL updated_map -> sedimap[i][k] = euler_step(i - updated_map -> velocity_field[i][k] -> x * TIME_STEP, k - updated_map -> velocity_field[i][k] -> y * TIME_STEP); END

        // evaporation
        FOR_EACH_CELL

            if (updated_map -> watermap[i][k] <= 0.001) updated_map -> watermap[i][k] = 0;
            updated_map -> watermap[i][k] *= (1 - evaporation_rate * TIME_STEP);

        END

        // update parameters for next iteration
        FOR_EACH_CELL update_cell(i, k); END

    }

    while(is_wet()) {

        // compute new flux
        FOR_EACH_CELL scale_flux(i, k, heightmap[i][k] + current_map -> watermap[i][k]); END

        // update water level based on flux
        FOR_EACH_CELL update_water_level(i, k); END

        // velocity field
        FOR_EACH_CELL updated_map -> update_velocity(i, k, current_map -> watermap[i][k], updated_map -> watermap[i][k]); END

        // erosion and deposition
        FOR_EACH_CELL erosion_deposition(i, k); END

        // update sediment
        FOR_EACH_CELL heightmap[i][k] += temp_heightmap[i][k]; END

        // sediment transport
        FOR_EACH_CELL updated_map -> sedimap[i][k] = euler_step(i - updated_map -> velocity_field[i][k] -> x * TIME_STEP, k - updated_map -> velocity_field[i][k] -> y * TIME_STEP); END

        // evaporation
        FOR_EACH_CELL

            updated_map -> watermap[i][k] *= (1 - post_evaporation_rate * TIME_STEP);
            updated_map -> watermap[i][k] -= MINIMUM_EVAPORATION_THRESHOLD;
            if (updated_map -> watermap[i][k] <= 0.001) updated_map -> watermap[i][k] = 0;

        END

        // update parameters for next iteration
        FOR_EACH_CELL update_cell(i, k); END

    }

    // output results
    output_heightmap();

    current_map -> velocity_field.clear();
    current_map -> velocity_field.clear();
    updated_map -> flux_field.clear();
    updated_map -> flux_field.clear();

    delete current_map;
    delete updated_map;

}


void hydro :: output_heightmap() {

    std :: ofstream happy_file;

    // eroded heightmap for rendering
    happy_file.open("../terrain/heightmap_eroded.pgm");
    happy_file << "P2\n";
    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
    happy_file << "65535\n";

    FOR_EACH_CELL

        if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << ceil(heightmap[i][k] * 400) << '\n';
        else happy_file << ceil(heightmap[i][k] * 400)  << ' ';

    END

    happy_file.close();

    // eroded heightmap for preview
    happy_file.open("../terrain/heightmap_eroded_preview.ppm");
    happy_file << "P3\n";
    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
    happy_file << "65535\n";

    FOR_EACH_CELL

            happy_file << static_cast <int> (ceil(heightmap[i][k] * 400 * 0.85)) << ' ';
            happy_file << static_cast <int> (ceil(heightmap[i][k] * 400 * 0.85)) << ' ';

//            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << heightmap[i][k] << '\n';
//            else happy_file << static_cast <int> (heightmap[i][k]) << ' ';



        if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << ceil(heightmap[i][k] * 400) << '\n';
        else happy_file << ceil(heightmap[i][k] * 400) << ' ';

    END

    happy_file.close();

}


void hydro :: dynamic_load() {

    load_heightmap();

    FOR_EACH_CELL heightmap[i][k] /= NORMALIZATION_FACTOR ; END

    current_map = new hydro_map(static_cast <int> (heightmap.size()), static_cast <int> (heightmap[0].size()));
    updated_map = new hydro_map(static_cast <int> (heightmap.size()), static_cast <int> (heightmap[0].size()));

}



void hydro :: big_drop(int x, int y) {
    int factor = 24;
    if (rand() % factor == 0) {
        float amount = factor * water * TIME_STEP;
        for (int i = -1; i < 2; i++) {
            for (int k = -1; k < 2; k++) {
                if (is_in_bounds(x + i, y + k) && !(i == 0 && k == 0)) {
                    current_map -> watermap[x + i][y + k] += (amount / (factor / 9));
                    amount -= (amount / (factor / 9));
                }
            }
        }

        current_map -> watermap[x][y] += amount;
    }
}


void hydro :: dynamic_erode() {

    FOR_EACH_CELL current_map -> watermap[i][k] += 0.5 * water * TIME_STEP + (0.5 * water * TIME_STEP * (rand() % 3)); END

    // compute new flux
    FOR_EACH_CELL scale_flux(i, k, heightmap[i][k] + current_map -> watermap[i][k]); END

    // update water level based on flux
    FOR_EACH_CELL update_water_level(i, k); END

    // velocity field
    FOR_EACH_CELL updated_map -> update_velocity(i, k, current_map -> watermap[i][k], updated_map -> watermap[i][k]); END

    // erosion and deposition
    FOR_EACH_CELL erosion_deposition(i, k); END

    // update sediment
    FOR_EACH_CELL heightmap[i][k] += temp_heightmap[i][k]; END

    // sediment transport
    FOR_EACH_CELL updated_map -> sedimap[i][k] = euler_step(i - updated_map -> velocity_field[i][k] -> x * TIME_STEP, k - updated_map -> velocity_field[i][k] -> y * TIME_STEP); END

    // evaporation
    FOR_EACH_CELL

        updated_map -> watermap[i][k] *= (1 - evaporation_rate * TIME_STEP);
        if (updated_map -> watermap[i][k] <= 0.001) updated_map -> watermap[i][k] = 0;

    END

    // update parameters for next iteration
    FOR_EACH_CELL update_cell(i, k); END

}

void hydro :: dynamic_evaporate() {

    // compute new flux
    FOR_EACH_CELL scale_flux(i, k, heightmap[i][k] + current_map -> watermap[i][k]); END

    // update water level based on flux
    FOR_EACH_CELL update_water_level(i, k); END

    // velocity field
    FOR_EACH_CELL updated_map -> update_velocity(i, k, current_map -> watermap[i][k], updated_map -> watermap[i][k]); END

    // erosion and deposition
    FOR_EACH_CELL erosion_deposition(i, k); END

    // update sediment
    FOR_EACH_CELL heightmap[i][k] += temp_heightmap[i][k]; END

    // sediment transport
    FOR_EACH_CELL updated_map -> sedimap[i][k] = euler_step(i - updated_map -> velocity_field[i][k] -> x * TIME_STEP, k - updated_map -> velocity_field[i][k] -> y * TIME_STEP); END

    // evaporation
    FOR_EACH_CELL

        updated_map -> watermap[i][k] *= (1 - post_evaporation_rate * TIME_STEP);
        updated_map -> watermap[i][k] -= MINIMUM_EVAPORATION_THRESHOLD;
        if (updated_map -> watermap[i][k] <= 0.001) updated_map -> watermap[i][k] = 0;

    END

    // update parameters for next iteration
    FOR_EACH_CELL update_cell(i, k); END

}


void hydro :: dynamic_delete() {

    current_map -> velocity_field.clear();
    current_map -> velocity_field.clear();
    updated_map -> flux_field.clear();
    updated_map -> flux_field.clear();

    delete current_map;
    delete updated_map;

}



bool hydro :: is_wet() {

    FOR_EACH_CELL if (current_map -> watermap[i][k] > 0) return true; END

    return false;

}


bool hydro :: is_in_bounds(int x, int y) {

    IF_OUT_OF_BOUNDS return false;

    return true;
}
