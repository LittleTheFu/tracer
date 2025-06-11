#ifndef _LAMBERTIANREFLECTION_H_
#define _LAMBERTIANREFLECTION_H_

#include "bxdf.h"

class LambertianReflection : public Bxdf
{
public:
    LambertianReflection(const Color &reflectance);

    virtual Color f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const override;

private:
    Color reflectance_;
};

#endif