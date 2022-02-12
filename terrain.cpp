

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


terrain :: terrain() : terrain_size(0) {

    triangles_count = 0;
}


void terrain :: load_heightmap() {

    using namespace std;

    // open .pgm image
    ifstream terrain_data("../terrain/heightmap2.pgm");

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


// compute normals
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

void terrain :: load_arrays() {

    triangles_count = num_triangles();
    terrain_positions = new float[triangles_count * 9];
    terrain_normals = new float[triangles_count * 9];

    int counter = 0;

    for (int i = 0; i < terrain_triangle_mx.size(); i++) {

        for (int k = 0; k < terrain_triangle_mx[i].size(); k++) {

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
            terrain_normals[counter   *   9] = terrain_triangle_mx[i][k].vertex_1.normal_x;
            terrain_normals[counter * 9 + 1] = terrain_triangle_mx[i][k].vertex_1.normal_y;
            terrain_normals[counter * 9 + 2] = terrain_triangle_mx[i][k].vertex_1.normal_z;

            terrain_normals[counter * 9 + 3] = terrain_triangle_mx[i][k].vertex_2.normal_x;
            terrain_normals[counter * 9 + 4] = terrain_triangle_mx[i][k].vertex_2.normal_y;
            terrain_normals[counter * 9 + 5] = terrain_triangle_mx[i][k].vertex_2.normal_z;

            terrain_normals[counter * 9 + 6] = terrain_triangle_mx[i][k].vertex_3.normal_x;
            terrain_normals[counter * 9 + 7] = terrain_triangle_mx[i][k].vertex_3.normal_y;
            terrain_normals[counter * 9 + 8] = terrain_triangle_mx[i][k].vertex_3.normal_z;

            counter++;
        }
    }

}


void terrain :: load_terrain() {

    load_heightmap();
    load_triangles();
    normalize_terrain(5);
    stretch_terrain(8, 8);
    load_normals();
    load_arrays();
}


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

void terrain :: draw_terrain_arrays() {

    glPushMatrix();
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   m200.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  m200.specular);
    glMaterialf( GL_FRONT, GL_SHININESS, m200.shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   m200.ambient);

    glVertexPointer(3, GL_FLOAT, 0, terrain_positions);
    glNormalPointer(GL_FLOAT, 0, terrain_normals);
    glDrawArrays( GL_TRIANGLES, 0, triangles_count * 3);

    glPopMatrix();
}


void terrain :: normalize_terrain(int factor) {

    for (int i = 0; i < terrain_triangle_mx.size(); i++) {
        for (int k = 0; k < terrain_triangle_mx[i].size(); k++) {
            terrain_triangle_mx[i][k].vertex_1.position_z /= factor;
            terrain_triangle_mx[i][k].vertex_2.position_z /= factor;
            terrain_triangle_mx[i][k].vertex_3.position_z /= factor;
        }
    }
}


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


int terrain :: num_triangles() {
    int num = 0;
    for (int i = 0; i < terrain_triangle_mx.size(); i++) num += terrain_triangle_mx[i].size();
    return num;
}


//void terrain :: set_vbo() {

//    load_terrain();

////    glEnableClientState(GL_VERTEX_ARRAY);
////    glEnableClientState(GL_NORMAL_ARRAY);

//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, triangles_count * 9 * sizeof(float), terrain_positions, GL_STATIC_DRAW);
//}

