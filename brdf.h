#ifndef _BRDF_H_
#define _BRDF_H_

#include "vector.h"
#include "color.h"

class Brdf
{
public:
    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) = 0;
    virtual bool isMirror() const;
    virtual bool isGlass() const;

    const static Vector3 LOCAL_NORMAL;
};

#endif