#ifndef _DIELECTRIC_BXDF_H_
#define _DIELECTRIC_BXDF_H_

#include "bxdf.h"

class DielectricBxdf : public Bxdf
{
public:
    DielectricBxdf(float ior);

    virtual Color f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const override;
private:
    float ior_;
};

#endif