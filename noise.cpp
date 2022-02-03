#include "noise.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

#define MAP_SIZE 200

noise :: noise() {
//    std :: ofstream happy_file;
//    happy_file.open("heightmap.pgm");
//    happy_file << "P2\n";
//    happy_file << "100 100\n";
//    happy_file << "255\n";

//    for (int i = 0; i < 100; i++) {
//        for (int k = 0; k < 100; k++) {
//            if (k == 99) {
//                happy_file << rand() % 255 << "\n";
//                break;
//            }
//            happy_file << rand() % 255 << " ";
//        }

//    }
//    happy_file.close();
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
