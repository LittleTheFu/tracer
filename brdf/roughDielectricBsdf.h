#ifndef _ROUGHDIELECTRIC_BSDF_H_
#define _ROUGHDIRLECTRIC_BSDF_H_

#include "brdf.h"

class RoughDielectricBsdf : public Brdf
{
public:
    RoughDielectricBsdf(float roughness, float ior);

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const override;

    virtual Color get_f(const Vector3 &wo, const Vector3 &wi) const override;

    virtual float pdf(const Vector3 &wo, const Vector3&wi) const override; 
};  

#endif