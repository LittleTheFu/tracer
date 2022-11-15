#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include "brdf.h"
#include "color.h"

class Lambertian : public Brdf
{
public:
    Lambertian(float scale);

    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const;
    void setColor(const Color &color);

private:
    Color m_color;
    float m_scale;
};

#endif