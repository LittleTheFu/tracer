#ifndef _DIELECTRIC_BXDF_H_
#define _DIELECTRIC_BXDF_H_

#include "bxdf.h"

class DielectricBxdf : public Bxdf
{
public:
    DielectricBxdf(float etaI, float etaT);

    virtual Color f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const override;
private:
    float etaI_;
    float etaT_;
};

#endif