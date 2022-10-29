#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include "brdf.h"

class Lambertian : public Brdf
{
public:
    Lambertian(float rho);
    float sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) = 0;

private:
    float m_rho;
};

#endif