#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include "brdf.h"
#include "color.h"

class Lambertian : public Brdf
{
public:
    Lambertian(Color rho);
    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf);

// private:
    Color m_rho;
};

#endif