#ifndef _MIRROR_H_
#define _MIRROR_H_

#include "brdf.h"

class Mirror : public Brdf
{
public:
    float sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) = 0;
};

#endif