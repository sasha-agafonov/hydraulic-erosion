#ifndef HYDRO_FLUX_H
#define HYDRO_FLUX_H


class hydro_flux {

public:

    hydro_flux();

    float up;
    float down;
    float left;
    float right;

    float sum();
    void scale(float scale);
    void set_zeroes();

};

#endif // HYDRO_FLUX_H
