#include "hydro2.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#define PGM_8_BIT 255
#define PGM_16_BIT 65535
#define OUT_OF_BOUNDS -1

#define SOLUBILITY 0.1
#define EVAPRATE 0.5
#define CAPACITY 0.1

hydro2 :: hydro2() {}


void hydro2 :: load_heightmap() {

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


void hydro2 :: create_bounded_heightmap() {

    bounded_heightmap.clear();

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {

        if (i == 0) {
            std :: vector <float> bounded_row;
            for (int b = 0; b < static_cast <int> (heightmap[0].size()) + 2; b++) bounded_row.push_back(OUT_OF_BOUNDS);
            bounded_heightmap.push_back(bounded_row);
        }

        std :: vector <float> row;

        row.push_back(OUT_OF_BOUNDS);

        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) row.push_back(heightmap[i][k]);

        row.push_back(OUT_OF_BOUNDS);

        bounded_heightmap.push_back(row);

        if (i == static_cast <int> (heightmap.size()) - 1) {
            std :: vector <float> bounded_row;
            for (int b = 0; b < static_cast <int> (heightmap[0].size()) + 2; b++) bounded_row.push_back(OUT_OF_BOUNDS);
            bounded_heightmap.push_back(bounded_row);
        }

    }
}

void hydro2 :: create_bounded_watermap() {

    bounded_watermap.clear();

    int bound_x = static_cast <int> (bounded_heightmap.size()) - 1;
    int bound_y = static_cast <int> (bounded_heightmap[0].size()) - 1;

    for (int i = 0; i < static_cast <int> (bounded_heightmap.size()); i++) {

        std :: vector <float> row;

        for (int k = 0; k < static_cast <int> (bounded_heightmap[0].size()); k++) {
            if (i == 0 || i == bound_x || k == 0 || k == bound_y) row.push_back(OUT_OF_BOUNDS);
            else row.push_back(0);
        }

        bounded_watermap.push_back(row);
    }
}

void hydro2 :: create_sediment_map() {

    sediment_map.clear();

    int bound_x = static_cast <int> (bounded_heightmap.size()) - 1;
    int bound_y = static_cast <int> (bounded_heightmap[0].size()) - 1;

    for (int i = 0; i < static_cast <int> (bounded_heightmap.size()); i++) {

        std :: vector <float> row;

        for (int k = 0; k < static_cast <int> (bounded_heightmap[0].size()); k++) {
            if (i == 0 || i == bound_x || k == 0 || k == bound_y) row.push_back(OUT_OF_BOUNDS);
            else row.push_back(0);
        }

        sediment_map.push_back(row);
    }
}


void hydro2 :: distribute_water(int units) {

    int size_x = bounded_watermap.size();
    int size_y = bounded_watermap[0].size();

    for (int i = 0; i < units; i++) bounded_watermap[(rand() % (size_x - 2)) + 1][(rand() % (size_y - 2)) + 1] += 10;

}

void hydro2 :: erode(int steps) {



    while(steps > 0) {

        steps--;

        //rows
        for (int i = 1; i < static_cast <int> (bounded_watermap.size()) - 1; i++) {

            //cols
            for (int k = 1; k < static_cast <int> (bounded_watermap[0].size()) - 1; k++) {

                bounded_watermap[i][k] += 8;

                // the current cell
                neighbour current;


                current.index_x = i;
                current.index_y = k;
                current.water_height = bounded_watermap[i][k];
                current.land_height = bounded_heightmap[i][k];
                current.total_height = current.water_height + current.land_height;
                current.sediment = sediment_map[i][k];





                float max_capacity = CAPACITY * bounded_watermap[i][k];
                float free_capacity = max_capacity - sediment_map[i][k];
//                std :: cout << " water: " << bounded_watermap[i][k] << " max_capacity: " << max_capacity << " free: " << free_capacity;

                // if there is enough material to erode
//                if (bounded_heightmap[i][k] >= max_capacity) {

                    // maximum cap minus current sediment amount



                    if (free_capacity >= SOLUBILITY * bounded_watermap[i][k] && bounded_heightmap[i][k] >= 0.01 * bounded_watermap[i][k]) {

                        bounded_heightmap[i][k] -= SOLUBILITY * bounded_watermap[i][k];
                        sediment_map[i][k] += SOLUBILITY * bounded_watermap[i][k];
                    }

                    else if (free_capacity >= SOLUBILITY * bounded_watermap[i][k] && bounded_heightmap[i][k] < 0.01 * bounded_watermap[i][k]) {

                        sediment_map[i][k] += bounded_heightmap[i][k];
                        bounded_heightmap[i][k] = 0;
                    }

//                    else if (free_capacity < SOLUBILITY * bounded_heightmap[i][k]) {
                    else {
                        if (bounded_heightmap[i][k] > free_capacity) {
                            sediment_map[i][k] += free_capacity;
                            bounded_heightmap[i][k] -= free_capacity;
                        }
                        else {
                            sediment_map[i][k] += bounded_heightmap[i][k];
                            bounded_heightmap[i][k] = 0;
                        }
                    }



                if (bounded_watermap[i][k] > 0.1) {
                // identify the 8 neighbouring cells
                std :: vector <neighbour> neighbours;

                for (int nx = -1; nx < 2; nx++) {

                    for (int ny = -1; ny < 2; ny++) {

                        if ((nx != 0 || ny != 0) && bounded_heightmap[i + nx][k + ny] != OUT_OF_BOUNDS) {

                          neighbour nbr;

                          nbr.index_x = i + nx;
                          nbr.index_y = k + ny;
                          nbr.water_height = bounded_watermap[i + nx][k + ny];
                          nbr.land_height = bounded_heightmap[i + nx][k + ny];
                          nbr.total_height = nbr.water_height + nbr.land_height;
                          nbr.sediment = sediment_map[i + nx][k + ny];

                          if (nbr.total_height < current.total_height) neighbours.push_back(nbr);

                        }
                    }
                }



                    float average_height = current.total_height;
                    float total_difference = 0;

                    for (int nbr = 0; nbr < static_cast <int> (neighbours.size()); nbr++) {
                        average_height += neighbours[nbr].total_height;
                        total_difference += (current.total_height - neighbours[nbr].total_height);

                    }

                    average_height /= (static_cast <int> (neighbours.size()) + 1);

                    // finally, distribute water

                    float all_water = current.water_height;

                    for (int nbr = 0; nbr < static_cast <int> (neighbours.size()); nbr++ ) {

                        float water_transfer = (std :: min (current.water_height, current.total_height - average_height)
                                             * (current.total_height - neighbours[nbr].total_height) / total_difference);

                        neighbours[nbr].water_height += water_transfer;

                        bounded_watermap[neighbours[nbr].index_x][neighbours[nbr].index_y] = neighbours[nbr].water_height;

                        current.water_height -= water_transfer;

                        // transfer some sediment proportional to the amount of transfered water

                        float sediment_transfer = sediment_map[i][k] * (water_transfer / all_water );

                        sediment_map[neighbours[nbr].index_x][neighbours[nbr].index_y] += sediment_transfer;

                        sediment_map[i][k] -= sediment_transfer;
                    }

                    bounded_watermap[current.index_x][current.index_y] = current.water_height;
                }

//                if (bounded_watermap[current.index_x][current.index_y] < 0) bounded_watermap[current.index_x][current.index_y] = 0;

                // evaporate some water

                if (bounded_watermap[current.index_x][current.index_y] > 0.01)
                bounded_watermap[current.index_x][current.index_y] *= (1 - EVAPRATE);

                // sediment if new carry capacity exceeded

                float carry_capacity = CAPACITY * bounded_watermap[current.index_x][current.index_y];

                if (sediment_map[i][k] > carry_capacity) {
                    float drop = sediment_map[i][k] - carry_capacity;

                    bounded_heightmap[i][k] += drop;
                    sediment_map[i][k] -= drop;

                }
            }
        }
    }
}


void hydro2 :: drop() {
    for (int i = 1; i < bounded_heightmap.size() - 1 ; i++) {
        for (int k = 1; k < bounded_heightmap[0].size() - 1; k++) {
//            std :: cout << bounded_heightmap[i][k] << "p";
            heightmap[i - 1][k - 1] = bounded_heightmap[i][k];
//            std :: cout << bounded_heightmap[i][k];

        }
    }
}





void hydro2 :: output_heightmap() {

    std :: ofstream happy_file;

    // eroded heightmap for rendering
    happy_file.open("../terrain/heightmap_eroded2_preview.pgm");
    happy_file << "P2\n";
    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
    happy_file << "65535\n";

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << ceil(heightmap[i][k]) + 1<< '\n';
            else happy_file << ceil(heightmap[i][k]) + 1 << ' ';
        }
    }

    happy_file.close();
    // eroded heightmap for preview
//    happy_file.open("../terrain/test2.ppm");
//    happy_file << "P3\n";
//    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
//    happy_file << "65535\n";

//    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
//        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {

//            // make the eroded preview heightmap slightly blue
//            happy_file << static_cast <int> (floor(heightmap[i][k] * 0.85)) << ' ';
//            happy_file << static_cast <int> (floor(heightmap[i][k] * 0.85)) << ' ';

//            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << heightmap[i][k] << '\n';
//            else happy_file << static_cast <int> (heightmap[i][k]) << ' ';

//        }
//    }

//    happy_file.close();

}

