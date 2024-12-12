#ifndef _BRDF_H_
#define _BRDF_H_

#include "vector.h"
#include "color.h"

class Brdf
{
public:
    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const = 0;
    virtual Color get_f(const Vector3 &wo, const Vector3 &wi) const;

    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const;

    const static Vector3 LOCAL_NORMAL;
};

#endif