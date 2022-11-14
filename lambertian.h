#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include "brdf.h"
#include "color.h"

class Lambertian : public Brdf
{
public:
    Lambertian(float scale);
    Lambertian(const Color &rho, float scale);
    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const;

    void setRho(const Color &rho);

private:
    Color m_rho;
    float m_scale;
};

#endif