#ifndef _LAMBERTIAN_BXDF_H_
#define _LAMBERTIAN_BXDF_H_

#include "bxdf.h"

class LambertianBxdf : public Bxdf
{
public:
    LambertianBxdf(const Color &reflectance);

    virtual Color f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const override;


private:
    Color reflectance_;
};

#endif