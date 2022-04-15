#ifndef TERRAIN_H
#define TERRAIN_H

#include <GL/glu.h>
#include <vector>

#include "hydro.h"

typedef struct materialStruct {

    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;

} materialStruct;

static materialStruct rocky {
    { 0.7f, 0.7f, 0.7f, 1.f },
    { 0.01f, 0.01f, 0.01f, 1.f },
    { 0.01f, 0.01f, 0.01f, 1.f },
    1.f
};

static materialStruct m200 {
    { 0.6f, 1.2f,  0.6f, 1.f },
    { 0.04f, 0.05f, 0.04f, 1.f },
    { 0.03f, 0.1f,  0.03f, 1.f },
    2.f
};

static materialStruct whitesh {
    { 3.f, 3.f, 3.f, 1.f },
    { 0.01f, 0.01f, 0.01f, 1.f },
    { 0.05f, 0.05f,  0.05f, 1.f },
    2.f
};

static materialStruct base {
    { 0.1f, 0.1f, 0.1f, 1.f },
    { 0.1f, 0.1f, 0.1f, 1.f },
    { 0.05f, 0.05f, 0.05f, 1.f },
    2.f
};


typedef struct vertex {

    float position_x;
    float position_y;
    float position_z;

    float normal_x;
    float normal_y;
    float normal_z;

} vertex;

typedef struct triangle {

    vertex vertex_1;
    vertex vertex_2;
    vertex vertex_3;

} triangle;

class terrain {

public:

    terrain();

    void load_heightmap();
    void load_triangles();
    void load_normals();
    void load_smooth_normals();
    void load_arrays();
    void load_colors();
    void load_terrain();
    void load_hydro();

    hydro* hydraulic_erosion;
    int cycles;
    int current_cycle;

    bool dynamic;
    bool eroded;
    bool loaded;

    float vec_len(float x, float y, float z);
    float normal_angle(float x, float y, float z);

    float min;
    float max;

    int num_triangles();
    void draw_terrain();
    void draw_terrain_arrays();
    void normalize_terrain(int factor);
    void stretch_terrain(int stretch_x, int stretch_y);
    void minimax();

    int terrain_size;
    int triangles_count;

    float* terrain_positions;
    float* terrain_normals;

    std :: vector <float> terrain_colors;

    std :: vector < std :: vector <float> > terrain_numerical_mx;
    std :: vector < std :: vector <float> > terrain_numerical_mx_raw;

    std :: vector < std :: vector <triangle> > terrain_triangle_mx;
    std :: vector < std :: vector <triangle> > terrain_triangle_mx_original;
    std :: vector < std :: vector <triangle> > terrain_smooth_triangle_mx;

};

#endif // TERRAIN_H
