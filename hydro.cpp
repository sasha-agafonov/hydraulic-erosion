#include "hydro.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#define PGM_8_BIT 255
#define PGM_16_BIT 65535



hydro :: hydro() {
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

    for (int i = 0; i < terrain_size; i++) {

        getline(terrain_data, happy_string);

        istringstream unhappy_string_stream(happy_string);
        vector <float> pixel_row;

        while (getline(unhappy_string_stream, unhappy_string, ' ')) pixel_row.push_back(stof(unhappy_string));

        heightmap.push_back(pixel_row);
    }
}















void hydro :: load_surface_normals() {
    surface_normals.clear();
    surface_normal normal;
    normal.x = 0;
    normal.y = 0;
    normal.z = 0;

    for (int row = 0; row < heightmap.size(); row++) {
        std :: vector <surface_normal> normals_row;
        for (int col = 0; col < heightmap[0].size(); col++) {
            normal.height = heightmap[row][col];
            normals_row.push_back(normal);
        }
        surface_normals.push_back(normals_row);
    }

    for (int row = 0; row < heightmap.size(); row++) {
        for (int col = 0; col < heightmap[0].size(); col++) {
            if (row == 0 || col == 0 || col == heightmap.size() - 1  || row == heightmap.size() - 1) {
                surface_normals[row][col].x = 0;
                surface_normals[row][col].y = 0;
                surface_normals[row][col].z = 1;
            }
            else {



//                surface_normals[row][col].x = 0.5 * (heightmap[row][col + 1] / 400.f - heightmap[row][col - 1] / 400.f);
//                surface_normals[row][col].y = 0.5 * (heightmap[row + 1][col] / 400.f - heightmap[row - 1][col - 1] / 400.f);
//                surface_normals[row][col].z = 1;
                surface_normals[row][col].x = 0;
                surface_normals[row][col].x += (heightmap[row][col] - heightmap[row + 1][col]) / 400.f;
                surface_normals[row][col].x += (heightmap[row - 1][col] - heightmap[row][col]) / 400.f;

                surface_normals[row][col].y = 0;
                surface_normals[row][col].y += (heightmap[row][col] - heightmap[row][col + 1]) / 400.f;
                surface_normals[row][col].y += (heightmap[row][col - 1] - heightmap[row][col]) / 400.f;

                surface_normals[row][col].z = 1;


                vec_norm(row, col);
            }
        }
    }


}

void hydro :: vec_norm(int x, int y) {
    float fac = sqrt(pow(surface_normals[x][y].x, 2) + pow(surface_normals[x][y].y, 2) + pow(surface_normals[x][y].z, 2));
    surface_normals[x][y].x /= fac;
    surface_normals[x][y].y /= fac;
    surface_normals[x][y].z /= fac;

//    std :: cout << surface_normals[x][y].x << "x   \n";
//    std :: cout << surface_normals[x][y].y << "y   \n";
//    std :: cout << surface_normals[x][y].z << "z   \n";
}


void hydro :: load_tiles() {
    tiles.clear();
    tile new_tile;

    new_tile.terrain_height = 0;
    new_tile.water_height = 0;
    new_tile.sediment_amount = 0;
    new_tile.flux = 0;

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {

        std :: vector <tile> tile_row;

        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {

            new_tile.terrain_height = heightmap[i][k];
            tile_row.push_back(new_tile);
        }

        tiles.push_back(tile_row);
    }
}


void hydro :: rain() {
    int terrain_w = heightmap.size();
    int x = 0;
    int y = 0;

    for (int drops = 0; drops < pow(terrain_w, 2); drops++) {
        x = rand() % terrain_w;
        y = rand() % terrain_w;
        tiles[x][y].water_height += 10;
    }
}


void hydro :: test_water() {
    for (int i = 0; i < tiles.size(); i++) {
        for (int k = 0; k < tiles[0].size(); k++) {
            std :: cout << tiles[i][k].water_height;
        }
    }
}

void hydro :: erode() {
    load_heightmap();
    load_tiles();

    load_surface_normals();
    int terrain_w = heightmap.size();
    for (int drops = 0; drops < 10000; drops++) {
        rain_drop(rand() % terrain_w, rand() % terrain_w);
    }
    normalize_heightmap();
    write_heightmap();
//    rain();
//    test_water();
}


void hydro :: rain_drop(int pos_x, int pos_y) {

    int offset_x = (rand() % 3) - 1;
    int offset_y = (rand() % 3) - 1;
    float sed = 0;

    int x = pos_x;
    int y = pos_y;

    float xmv = floor(x );
    float ymv = floor(y);
    int prevx = x;
    int prevy = y;

    float prevz = 0;

    float vx = 0.1;
    float vy = 0.1;

    float nx;
    float ny;
    float nz;


    for (int it = 0; it < 60; it++) {

//        prevz = heightmap[floor(x)][floor(y)];
        int iteration = it;
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x > heightmap.size() - 1) x = heightmap.size() - 1;
        if (y > heightmap.size() - 1) y = heightmap.size() - 1;


        if (x > 2 && y > 2 && x < 498 && y < 498) {
         nx = surface_normals[x + offset_x][y + offset_y].x;
         ny = surface_normals[x + offset_x][y + offset_y].y;
         nz = surface_normals[x + offset_x][y + offset_y].z; }
        else {
        nx = surface_normals[x][y].x;
         ny = surface_normals[x][y].y;
        nz = surface_normals[x][y].z;

        }


        if (nz >= 0.95) {
            //heightmap[prevx][prevy] += sed;
            break;
        }


        float dep = sed * nz * iteration * 0.1f + 1;
        if (dep > sed) dep = sed;
        float er = (1 - nz * 1.3) * (300.f) / (iteration * 10 + 10) ;
                //100000 * (1 - nz) * (0.1 + it / 200.f);

//        heightmap[prevx][prevy] += dep;

        if (heightmap[prevx][prevy] > 0) {
        heightmap[prevx][prevy] -= er;
        if (vx < 0.1 && vy < 0.1) heightmap[prevx][prevy] += dep; }
//        heightmap[prevx][prevy] -= 1;

        sed += er;
        sed -= dep;

        vx = 0.9 * vx + 0.8 * nx;
        vy = 0.9 * vy + 0.8 * ny;

//        if (vx <= 0 || vy <= 0) break;

        prevx = x;
        prevy = y;

        xmv += vx;
        ymv += vy;

        x = floor(xmv);
        y = floor(ymv);

          // if (heightmap[prevx][prevy] < heightmap[x][y]) break;

    }
}


void hydro :: normalize_heightmap() {
    for (int i = 0; i < heightmap.size(); i++) {
        for (int k = 0; k < heightmap.size(); k++) {
                heightmap[i][k] = floor(heightmap[i][k]);
        }
    }
}

void hydro :: write_heightmap() {

    std :: ofstream happy_file;

    // eroded heightmap for rendering
    happy_file.open("../terrain/heightmap_eroded.pgm");
    happy_file << "P2\n";
    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
    happy_file << "65535\n";

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << heightmap[i][k] << '\n';
            else happy_file << heightmap[i][k] << ' ';
        }
    }

    happy_file.close();

    // eroded heightmap for preview
    happy_file.open("../terrain/heightmap_eroded_preview.ppm");
    happy_file << "P3\n";
    happy_file << heightmap.size() << ' ' << heightmap[0].size() << '\n';
    happy_file << "65535\n";

    for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
        for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {

            // make the eroded preview heightmap slightly blue
            happy_file << static_cast <int> (floor(heightmap[i][k] * 0.85)) << ' ';
            happy_file << static_cast <int> (floor(heightmap[i][k] * 0.85)) << ' ';

            if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << heightmap[i][k] << '\n';
            else happy_file << static_cast <int> (heightmap[i][k]) << ' ';

        }
    }

    happy_file.close();

}




//void hydro :: accumulate() {
//    for (int i = 0; i < tiles.size(); i++) {
//        for (int k = 0; k < tiles.size(); k++) {
//            if (tiles[i][k].water_height > 0) {
//                if (tiles[i][k].terrain_height > 0 && tiles[i][k].sediment_amount < tiles[i][k].water_height) {
//                    tiles[i][k].terrain_height -= 0.1;
//                    tiles[i][k].sediment_amount += 0.1;
//                }
//            }
//        }
//    }
//}

//void hydro :: flow() {
//    int flux_x = 0;
//    int flux_y = 0;
//    float min_height = 0;
//    for (int i = 1; i < tiles.size() - 1; i++) {
//        for (int k = 1; k < tiles.size() - 1; k++) {

//            min_height = tiles[i][k].terrain_height;


//            if (tiles[i][k + 1].terrain_height + tiles[i][k + 1].water_height < min_height) {
//                min_height = tiles[i][k + 1].terrain_height;
//                flux_x = 0;
//                flux_y = 1;
//            }
//            if (tiles[i + 1][k].terrain_height + tiles[i + 1][k].water_height < min_height) {
//                min_height = tiles[i + 1][k].terrain_height;
//                flux_x = 1;
//                flux_y = 0;
//            }
//            if (tiles[i][k - 1].terrain_height + tiles[i][k - 1].water_height < min_height) {
//                min_height = tiles[i][k - 1].terrain_height;
//                flux_x = 0;
//                flux_y = -1;
//            }
//            if (tiles[i - 1][k].terrain_height + tiles[i - 1][k].water_height < min_height) {
//                min_height = tiles[i - 1][k].terrain_height;
//                flux_x = -1;
//                flux_y = 0;
//            }

////            if (flux_x != 0 && flux_y != 0) {
////                if (tiles[i + flux_x][k + flux_y].water_height > 0) {
////                    float norm = (tiles[i][k].terrain_height + tiles[i][k].water_height
////                               + tiles[i + flux_x][k + flux_y].terrain_height + tiles[i + flux_x][k + flux_y].water_height) / 2.f;

////                }
////            }

//        }
//    }
//}











void hydro :: initialize_water_map() {
    water_map.clear();


    for (int i = 0; i < water_map.size(); i++ ) {
        std :: vector <float> water_row;
        for (int k = 0; k < water_map.size(); k++) {
            water_row.push_back(0);
        }
    }
}



void hydro :: spawn_drop() {
    water_map[rand() % water_map.size()][rand() % water_map[0].size()] += 1.f;

}

void hydro :: erode(int cycles) {

    for (int i = 0; i < cycles; i++) {
        for (int k = 0; k < 1000; k++) {

        }
    }
}
