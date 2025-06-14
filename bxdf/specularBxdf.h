#ifndef _SPECULAR_BXDF_H_
#define _SPECULAR_BXDF_H_

#include "bxdf.h"

class SpecularBxdf : public Bxdf
{
public:
    SpecularBxdf();

    Color f(const Vector3 &wo, const Vector3 &wi) const override;
    float pdf(const Vector3 &wo, const Vector3 &wi) const override;

    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const override;
};

#endif