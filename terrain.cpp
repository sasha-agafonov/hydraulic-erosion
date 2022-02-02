#include "terrain.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#define PGM_8_BIT 255
#define PGM_16_BIT 65535


terrain :: terrain() : terrain_size(0) {}

//void terrain :: load_terrain(void) {

//    using namespace std;

//    // open .pgm image
//    ifstream terrain_data("heightmap.pgm");

//    // or don't
//    if (terrain_data.fail()) throw "terrain.pgm is missing";

//   // int terrain_size = 0;
//    string happy_string, unhappy_string, str;
//    istringstream happy_string_stream;

//    // image file checks
//    for (int i = 0; i < 3; i++) {
//        getline(terrain_data, happy_string);

//        // check P2 header
//        if (i == 0 && happy_string.compare("P2") != 0) throw "P2 header missing";

//        // get terrain dimensions
//        else if (i == 1) { terrain_size = stoi(happy_string.substr(0, happy_string.find(' ')));

//        }

//        // accept 8-bit or 16-bit pgm only.
//        else if (i == 2 && stoi(happy_string) != PGM_8_BIT && stoi(happy_string) != PGM_16_BIT) throw "wrong bits per color specified in terrain.pgm";
//    }

//    //for (int i = 0; i < terrain_data.size(); i++) terrain_data[i].clear();

////    if (terrain_mx.size() > 0) for (int i = 0; i < terrain_mx.size(); i++) terrain_mx[i].clear();
//    terrain_mx.clear();

//    triangle happy_triangle;

//    vertex happy_vertex;
////    vertex vertex_2;
////    vertex vertex_3;
//    //terrain_mx.resize(terrain_size, vector <int> (terrain_size));
//    int subcounter;


//    for (int terrain_row = 0; terrain_row < terrain_size; terrain_row++) {

//        subcounter = 0;

//        getline(terrain_data, happy_string);

//        istringstream unhappy_string_stream(happy_string);
//        vector <triangle> triangle_row;
//            cout << terrain_size << "\n";

//        while (getline(unhappy_string_stream, unhappy_string, ' ')) {

//            happy_vertex.position_x = subcounter;
//            happy_vertex.position_y = terrain_row;
//            happy_vertex.position_z = stod(unhappy_string);

//            if (terrain_row == terrain_size - 1) { // last row, no need for new triangles

//                 if (subcounter == 0 ) terrain_mx[terrain_row][0].vertex_2 = happy_vertex;
//                 else if (subcounter == terrain_size - 1) terrain_mx[terrain_row][subcounter - 1].vertex_3 = happy_vertex;
//                 else {
//                    terrain_mx[terrain_row][subcounter - 1].vertex_3 = happy_vertex;
//                    terrain_mx[terrain_row][subcounter].vertex_2 = happy_vertex;
//                 }

//            } else {

//                if (subcounter < terrain_size - 1) {
//                    happy_triangle.vertex_1 = happy_vertex;
//                    triangle_row.push_back(happy_triangle);
//                    triangle_row.push_back(happy_triangle);
//                } else terrain_mx[terrain_row][subcounter - 1].vertex_3 = happy_vertex; // last pixel in this row
//            }
//            subcounter++;
//        }
//        terrain_mx.push_back(triangle_row);

//        cout << terrain_mx.size() << "terra size \n";

//        for (int i = 0; i < terrain_mx.size(); i++) {
//            cout << terrain_mx[i][terrain_mx.size() -1].vertex_3.position_z << "last el \n";
//        }

//    }
//    //return terrain_mx;
//}




void terrain :: load_heightmap() {

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

    terrain_numerical_mx.clear();

    for (int i = 0; i < terrain_size; i++) {

        getline(terrain_data, happy_string);

        istringstream unhappy_string_stream(happy_string);
        vector <double> pixel_row;

        while (getline(unhappy_string_stream, unhappy_string, ' ')) pixel_row.push_back(stod(unhappy_string));

        terrain_numerical_mx.push_back(pixel_row);
    }

}

void terrain :: load_triangles() {

//    v1--------v4
//    | ⟍       |
//    |   ⟍  t2 |
//    | t1  ⟍   |
//    |       ⟍ |
//    v2--------v3

    terrain_triangle_mx.clear();

    triangle happy_triangle_1, happy_triangle_2;
    vertex happy_vertex_1, happy_vertex_2;
    vertex happy_vertex_3, happy_vertex_4;


    for (int row = 0; row < terrain_numerical_mx.size() - 1; row++) {

        std :: vector <triangle> triangle_row;

        for (int col = 0; col < terrain_numerical_mx[0].size() - 1; col++) {

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

            happy_triangle_1.vertex_1 = happy_vertex_1;
            happy_triangle_2.vertex_1 = happy_vertex_1;

            happy_triangle_1.vertex_2 = happy_vertex_3;
            happy_triangle_2.vertex_2 = happy_vertex_4;

            happy_triangle_1.vertex_3 = happy_vertex_2;
            happy_triangle_2.vertex_3 = happy_vertex_3;

            triangle_row.push_back(happy_triangle_1);
            triangle_row.push_back(happy_triangle_2);

        }

        terrain_triangle_mx.push_back(triangle_row);

    }
}

void terrain :: load_normals() {

    triangle happy_triangle;

    for (int row = 0; row < terrain_triangle_mx.size(); row++) {
        for (int col = 0; col < terrain_triangle_mx[0].size(); col++) {

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

void terrain :: load_terrain() {

    load_heightmap();
    load_triangles();
    load_normals();
}

void terrain :: draw_terrain() {

    glPushMatrix();

         glMaterialfv(GL_FRONT, GL_DIFFUSE,   m200.diffuse);
         glMaterialfv(GL_FRONT, GL_SPECULAR,  m200.specular);
         glMaterialf( GL_FRONT, GL_SHININESS, m200.shininess);
         glMaterialfv(GL_FRONT, GL_AMBIENT,   m200.ambient);


        glTranslatef(-12., -12., -22);
        glScalef(8, 8, 1);


    for (int row = 0; row < terrain_triangle_mx.size(); row++) {
        for (int col = 0; col < terrain_triangle_mx[0].size(); col++) {
            glBegin(GL_TRIANGLES);

            glNormal3f( terrain_triangle_mx[row][col].vertex_1.normal_x,   terrain_triangle_mx[row][col].vertex_1.normal_y,   terrain_triangle_mx[row][col].vertex_1.normal_z );
            glVertex3f( terrain_triangle_mx[row][col].vertex_1.position_x, terrain_triangle_mx[row][col].vertex_1.position_y, terrain_triangle_mx[row][col].vertex_1.position_z / 50);


            glNormal3f( terrain_triangle_mx[row][col].vertex_2.normal_x,   terrain_triangle_mx[row][col].vertex_2.normal_y,   terrain_triangle_mx[row][col].vertex_2.normal_z );
            glVertex3f( terrain_triangle_mx[row][col].vertex_2.position_x, terrain_triangle_mx[row][col].vertex_2.position_y, terrain_triangle_mx[row][col].vertex_2.position_z / 50);

            glNormal3f( terrain_triangle_mx[row][col].vertex_3.normal_x,   terrain_triangle_mx[row][col].vertex_3.normal_y,   terrain_triangle_mx[row][col].vertex_3.normal_z );
            glVertex3f( terrain_triangle_mx[row][col].vertex_3.position_x, terrain_triangle_mx[row][col].vertex_3.position_y, terrain_triangle_mx[row][col].vertex_3.position_z / 50);

            glEnd();
        }
    }

    glPopMatrix();
}

//void terrain :: test() {
//    this -> terrain_data.clear();
//    triangle happy_triangle;
//    vertex vertex_1;
//    vertex vertex_2;
//    vertex vertex_3;



//    for (int i = 0 ; i < 10; i++) {

//        vertex_1.position_x = i;
//        vertex_2.position_y = i + 1;
//        vertex_3.position_z = i * 2;

//        vertex_1.normal_x = i + 9;
//        vertex_2.normal_y = 34;
//        vertex_3.normal_z = 0;

//        happy_triangle.vertex_1 = vertex_1;
//        happy_triangle.vertex_2 = vertex_2;
//        happy_triangle.vertex_3 = vertex_3;

//        terrain_data.push_back(happy_triangle);
//    }
//    for (int i=0; i < terrain_data.size(); i++) {
//        std :: cout << terrain_data[i].vertex_1.normal_x << "\n";
//        std :: cout << terrain_data[i].vertex_2.normal_z << "\n";
//    }
//}


//void terrain :: draw_terrain(materialStruct* material) {
//    glPushMatrix();
//    glMaterialfv(GL_FRONT, GL_DIFFUSE,   material -> diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR,  material -> specular);
//    glMaterialf( GL_FRONT, GL_SHININESS, material -> shininess);
//    glMaterialfv(GL_FRONT, GL_AMBIENT,   material -> ambient);
//    glTranslatef(-12., -12., -22);



//    double ux, uy, uz;
//    double vx, vy, vz;
//    double nx, ny, nz;

//for (int row = 0; row < 99; row++) {
//    for (int col = 0; col < 99; col++) {


//        ux = row + 1 - row;
//        uy = col - col;
//        uz = (double) terrain_mx[row + 1][col] / 50 - (double) terrain_mx[row][col] / 50;

//        vx = row - row;
//        vy = col + 1 - col;
//        vz = (double)  terrain_mx[row][col + 1] / 50 - (double) terrain_mx[row][col] / 50;

//        nx = uy * vz - uz * vy;
//        ny = uz * vx - ux * vz;
//        nz = ux * vy - uy * vx;



//            glBegin(GL_TRIANGLES);
//            glNormal3f( nx, ny, nz );
//            glVertex3f( row, col, (double) terrain_mx[row][col] / 50);
//           // glNormal3f( rand() % 10, rand() % 10, rand() % 10 ); // probably a useless repeat for flat shading
//            glVertex3f( row + 1, col, (double) terrain_mx[row + 1][col] / 50);
//            //glNormal3f( rand() % 10, rand() % 10, rand() % 10 );
//            glVertex3f( row, col + 1, (double)  terrain_mx[row][col + 1] / 50);
//            glEnd();




//            ux = row + 1 - row;
//            uy = col - (col + 1);
//            uz = (double) terrain_mx[row + 1][col]/ 50 - (double) terrain_mx[row][col + 1] / 50;

//            vx = row + 1 - row;
//            vy = col + 1 - (col + 1);
//            vz = (double) terrain_mx[row + 1][col + 1] / 50 - (double) terrain_mx[row][col + 1] / 50;

//            nx = uy * vz - uz * vy;
//            ny = uz * vx - ux * vz;
//            nz = ux * vy - uy * vx;




//            glBegin(GL_TRIANGLES);
//            glNormal3f( nx, ny, nz );
//            glVertex3f( row, col + 1, (double) terrain_mx[row][col + 1] / 50);
//           // glNormal3f( rand() % 10, rand() % 10, rand() % 10 ); // probably a useless repeat for flat shading
//            glVertex3f( row + 1, col, (double) terrain_mx[row + 1][col]/ 50);
//            //glNormal3f( rand() % 10, rand() % 10, rand() % 10 );
//            glVertex3f( row + 1, col + 1, (double) terrain_mx[row + 1][col + 1] / 50);
//            glEnd();


//    }
//}


//    glPopMatrix();

//}
