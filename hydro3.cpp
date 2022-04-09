#include "hydro3.h"

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
#define OUT_OF_BOUNDS -1
#define GRAVITY 9.81f
#define FOR_EACH_CELL for (int i = 0; i < static_cast <int> (heightmap.size()); i++) { for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
#define END }}

hydro3 :: hydro3(QObject* parent) : QObject(parent) { connect(this, SIGNAL(reload_heightmap_signal()), parent, SLOT(reload_heightmap()));}


void hydro3 :: initialize_maps() {

    load_heightmap();
    normalize_heightmap();
    initialize_watermap();
    initialize_sedimap();
    initialize_flux_field();
    initilize_velocity_field();

}


void hydro3 :: load_heightmap() {

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

void hydro3 :: normalize_heightmap() { FOR_EACH_CELL heightmap[i][k] /= 400; END }


void hydro3 :: initialize_watermap() {

    watermap.clear();

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {

        std :: vector <float> row;

        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) row.push_back(0);

        watermap.push_back(row);

    }
}

void hydro3 :: initialize_sedimap() {

    sedimap.clear();

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {

        std :: vector <float> row;

        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) row.push_back(0);

        sedimap.push_back(row);

    }
}


void hydro3 :: initialize_flux_field() {

    flux_field.clear();

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {

        std :: vector <outflow_flux> flux_row;

        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {

            outflow_flux flux;
            flux.up = 0.f;
            flux.down = 0.f;
            flux.right = 0.f;
            flux.left = 0.f;
            flux_row.push_back(flux);
        }

        flux_field.push_back(flux_row);
    }
}


void hydro3 :: initilize_velocity_field() {

    velocity_field.clear();

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {

        std :: vector <velocity> velocity_row;

        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {

            velocity vel;
            vel.x = 0;
            vel.y = 0;
            velocity_row.push_back(vel);
        }

        velocity_field.push_back(velocity_row);
    }
}



outflow_flux hydro3 :: get_new_flux(int x, int y) {

    outflow_flux flux;

    float current_height = heightmap[x][y] + watermap[x][y];

    if (x - 1 < 0) flux.up = 0;
    else flux.up = std :: max(0.f, flux_field[x][y].up  + GRAVITY * (current_height - heightmap[x - 1][y] - watermap[x - 1][y]));

    if (y - 1 < 0) flux.left = 0;
    else flux.left = std :: max(0.f, flux_field[x][y].left  + GRAVITY * (current_height - heightmap[x][y - 1] - watermap[x][y - 1]));

    if (x + 1 >= static_cast <int> (heightmap.size())) flux.down = 0;
    else flux.down = std :: max(0.f, flux_field[x][y].down  + GRAVITY * (current_height - heightmap[x + 1][y] - watermap[x + 1][y]));

    if (y + 1 >= static_cast <int> (heightmap[0].size())) flux.right = 0;
    else flux.right = std :: max(0.f, flux_field[x][y].right  + GRAVITY * (current_height - heightmap[x][y + 1] - watermap[x][y + 1]));

    return flux;

}

float hydro3 :: get_inflow_flux(int x, int y, int from_x, int from_y) {

    if (from_x < 0 || from_y < 0 || from_x >= static_cast <int> (heightmap.size()) || from_y >= static_cast <int> (heightmap[0].size())) return 0.f;

    if (x < from_x) return flux_field[from_x][from_y].up;

    if (x > from_x) return flux_field[from_x][from_y].down;

    if (y < from_y) return flux_field[from_x][from_y].left;

    if (y > from_y) return flux_field[from_x][from_y].right;

    return -100.f;

}

void hydro3 :: update_flux(int x, int y) {

    if (x < 0 || y < 0 || x >= static_cast <int> (heightmap.size()) || y >= static_cast <int> (heightmap[0].size())) return;

    outflow_flux new_flux = get_new_flux(x, y);

//    if (isnan(new_flux.left)) std :: cout << "\nleft nan before: " << new_flux.left;


    if (new_flux.up + new_flux.down + new_flux.left + new_flux.right <= 0) {
        new_flux.left = 0;
        new_flux.right = 0;
        new_flux.up = 0;
        new_flux.down = 0;
    }
    else {
        float flux_scale;

        if (watermap[x][y] / (new_flux.up + new_flux.down + new_flux.left + new_flux.right) < 1) flux_scale = watermap[x][y] / (new_flux.up + new_flux.down + new_flux.left + new_flux.right);
        else flux_scale = 1;


//        = std :: min(1.f, watermap[x][y] / (new_flux.up + new_flux.down + new_flux.left + new_flux.right));

        new_flux.left = new_flux.left * flux_scale;

        new_flux.right *= flux_scale;
        new_flux.up *= flux_scale;
        new_flux.down *= flux_scale;
    }

//    if (isnan(new_flux.left)) std :: cout << "\nleft nan after: " << new_flux.left;

    flux_field[x][y] = new_flux;

//    watermap[x][y] += ((get_inflow_flux(x, y, x + 1, y) + get_inflow_flux(x, y, x - 1, y)
//                    + get_inflow_flux(x, y, x, y + 1) + get_inflow_flux(x, y, x, y - 1))
//                    - (new_flux.left + new_flux.right + new_flux.up + new_flux.down));
}

//void hydro3 :: update_water(int x, int y) {
//    watermap[x][y] +=
//}

void hydro3 :: check() {
    std :: cout << "xuyxuyxuy";
    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++ ) {
//            std :: cout << flux_field[i][k].up << " ";
//            std :: cout << flux_field[i][k].down << " ";
//            std :: cout << flux_field[i][k].left << " ";
//            std :: cout << flux_field[i][k].right << " ";

            std :: cout << heightmap[i][k] << " ";
        }
        std :: cout << "\n"; }
}



void hydro3 :: erode(int cycles) {

    bool ch = true;

    bool liar = true;

//    for (int x = 0; x < 100; x++) {
//    FOR_EACH_CELL watermap[i][k] += 0.01; update_flux(i, k); END
//    }


    for (int c = 0; c < cycles; c++) {



        FOR_EACH_CELL watermap[i][k] += 0.0001;

        update_flux(i, k);

        watermap[i][k] += get_inflow_flux(i, k, i + 1, k) + get_inflow_flux(i, k, i - 1, k) + get_inflow_flux(i, k, i, k + 1) + get_inflow_flux(i, k, i, k - 1) - flux_field[i][k].left - flux_field[i][k].right - flux_field[i][k].up - flux_field[i][k].down;
//
        if (watermap[i][k] < 0) watermap[i][k] = 0; END


//        FOR_EACH_CELL watermap[i][k] += 0.0001; END


//        FOR_EACH_CELL watermap[i][k] += 0.0001; END

//        FOR_EACH_CELL update_flux(i, k); END

//        FOR_EACH_CELL watermap[i][k] += get_inflow_flux(i, k, i + 1, k) + get_inflow_flux(i, k, i - 1, k) + get_inflow_flux(i, k, i, k + 1) + get_inflow_flux(i, k, i, k - 1) - flux_field[i][k].left - flux_field[i][k].right - flux_field[i][k].up - flux_field[i][k].down; END
////
//        FOR_EACH_CELL  if (watermap[i][k] < 0) watermap[i][k] = 0; END





//        for (int i = 0; i < heightmap.size(); i++) {
//            for (int k = 0; k < heightmap[0].size(); k++ ) {

//            watermap[i][k] += 100;
//            }
//        }


        // iterate over entire terrain
//        for (int e = 0; e < heightmap.size(); e++) {
//            for (int z = 0; z < heightmap[0].size(); z++ ) {

////                float water_gain;
//                update_flux(e, z);

//            }



//        for (int i = 0; i < heightmap.size(); i++) {
//            for (int k = 0; k < heightmap[0].size(); k++ ) {

////                float water_gain;

////            float left_inflow = get_inflow_flux(i, k, i + 1, k);
////            float right_inflow = get_inflow_flux(i, k, i - 1, k);
////            float up_inflow = get_inflow_flux(i, k, i, k + 1);
////            float down_inflow = get_inflow_flux(i, k, i, k - 1);


////            if (isnan(watermap[i][k]) && liar) {
////                std :: cout << "liar later\n";
////                liar = false;
////            }

//            if (watermap[i][k] < 0) watermap[i][k] = 0;
//        }
//    }

//        output_heightmap();
//         emit reload_heightmap_signal();

    }

//    for (int c = 0; c < cycles; c++) {
//        FOR_EACH_CELL update_flux(i, k); END

//        FOR_EACH_CELL watermap[i][k] += get_inflow_flux(i, k, i + 1, k) + get_inflow_flux(i, k, i - 1, k) + get_inflow_flux(i, k, i, k + 1) + get_inflow_flux(i, k, i, k - 1) - flux_field[i][k].left - flux_field[i][k].right - flux_field[i][k].up - flux_field[i][k].down; END
////
//        FOR_EACH_CELL  if (watermap[i][k] < 0) watermap[i][k] = 0; END
//    }
output_heightmap();
//                update_flux(i + 1, k);
//                update_flux(i - 1, k);
//                update_flux(i, k + 1);
//                update_flux(i, k - 1);

                // unlucky, nothing to do here
//                if (watermap[i][k] <= 0) continue;

//                update_segment(i, k);
//                update_segment

//                outflow_flux new_flux = get_new_flux(i, k);

//                float flux_scale = std :: min(1.f, watermap[i][k] / (new_flux.up + new_flux.down + new_flux.left + new_flux.right));

//                new_flux.left *= flux_scale;
//                new_flux.right *= flux_scale;
//                new_flux.up *= flux_scale;
//                new_flux.down *= flux_scale;

//                watermap[i][k] += ((get_inflow_flux(i, k, i + 1, k) + get_inflow_flux(i, k, i - 1, k)
//                                + get_inflow_flux(i, k, i, k + 1) + get_inflow_flux(i, k, i, k - 1))
//                                - (new_flux.left + new_flux.right + new_flux.up + new_flux.down));


}

void hydro3 :: output_heightmap() {

    std :: ofstream happy_file;

    // eroded heightmap for rendering
    happy_file.open("../terrain/heightmap_eroded2_preview.pgm");
    happy_file << "P2\n";
    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
    happy_file << "65535\n";

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << ceil((watermap[i][k] + heightmap[i][k]) * 400) << '\n';
            else happy_file << ceil((watermap[i][k] + heightmap[i][k]) * 400) << ' ';
        }
    }

    happy_file.close();

    happy_file.open("../terrain/waterters.pgm");
    happy_file << "P2\n";
    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
    happy_file << "65535\n";

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << ceil(watermap[i][k])<< '\n';
            else happy_file << ceil(watermap[i][k]) << ' ';
        }
    }

    happy_file.close();

}


// next position
// get terrain normal at current position.
// normal = normal_unit_vector(drop.x, drop.y)

// dissolve some water

// erode some water
//disp +=  vel + norm.x * sin(ang of incline)
//disp +=  vel + norm.y * sin (ang of incline)
// energy = 0.5 mv^2 where m = w

// erosion:
// change in energy * constant erosion rate




// if next energy lower, consume some material
// evaporate water
// if capacity low, drop material

// if water amount = 0; delete drop
//normal hydro3 :: normal_unit_vector(int x, int y) {

//    float top = bounded_heightmap[x][y + 1];
//    float bottom = bounded_heightmap[x][y - 1];
//    float right = bounded_heightmap[x + 1][y];
//    float left = bounded_heightmap[x - 1][y];

////    for (int i = 0; i < 4; i++) {

////    }


//    normal unit;
//    unit.x = 1;
//    unit.y = 1;
//    unit.z = 1;
//    return unit;

//}
