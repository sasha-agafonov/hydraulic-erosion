#ifndef TERRAIN_H
#define TERRAIN_H

#include <GL/glu.h>
#include <vector>

typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

static materialStruct m200 {
    { 0.6f, 1.2f,  0.6f, 1.f },
    { 0.04f, 0.05f, 0.04f, 1.f },
    { 0.03f, 0.1f,  0.03f, 1.f },
    2.f
};


typedef struct vertex {

    double position_x;
    double position_y;
    double position_z;

    double normal_x;
    double normal_y;
    double normal_z;

} vertex;

typedef struct triangle {

    vertex vertex_1;
    vertex vertex_2;
    vertex vertex_3;

} triangle;

class terrain {

public:
    terrain();
    int terrain_size;
    void load_terrain();
    void load_heightmap();
    void load_triangles();
    void load_normals();
    void draw_terrain();
    void test();

    std :: vector < std :: vector <double> > terrain_numerical_mx;
    std :: vector < std :: vector <triangle> > terrain_triangle_mx;

};



#endif // TERRAIN_H
