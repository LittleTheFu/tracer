#ifndef _BRDF_H_
#define _BRDF_H_

#include "vector.h"

class Brdf
{
public:
    virtual float sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) = 0;

    const static Vector3 LOCAL_NORMAL;
};

#endif