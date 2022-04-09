#ifndef HYDRO3_H
#define HYDRO3_H

#include <QObject>
#include <vector>

typedef struct normal {

    float x;
    float y;
    float z;

} normal;


typedef struct velocity {

    float x;
    float y;

} velocity;


typedef struct outflow_flux {

    float up;
    float down;
    float left;
    float right;

} outflow_flux;


class hydro3 : public QObject{

    Q_OBJECT



public:

    hydro3(QObject* parent);

    std :: vector <std :: vector <float> > heightmap;
    std :: vector <std :: vector <float> > watermap;
    std :: vector <std :: vector <float> > sedimap;

    std :: vector <std :: vector <velocity> > velocity_field;
    std :: vector <std :: vector <outflow_flux> > flux_field;


    void create_bounded_heightmap();
    void normalize_heightmap();
    void check();

    void load_heightmap();
    float get_inflow_flux(int x, int y, int from_x, int from_y);
    void initialize_flux_field();
    void initialize_watermap();
    void initialize_sedimap();
    void initilize_velocity_field();
    void initialize_maps();

    void output_heightmap();

    void update_flux(int x, int y);
    void update_water(int x, int y);

    void erode(int cycles);

    outflow_flux get_flux(int x, int y);
    void set_flux(int x, int y);

    float scale_flux(int x, int y);
    float get_total_height_difference(int x, int y, int xn, int yn);


    outflow_flux get_new_flux(int x, int y);
    normal normal_unit_vector(int x, int y);


signals:
    void reload_heightmap_signal();

};

#endif // HYDRO3_H
