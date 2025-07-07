#ifndef _MICROFACET_SPECULAR_BXDF_H_
#define _MICROFACET_SPECULAR_BXDF_H_

#include "bxdf.h"

class MicrofacetSpecularBxdf : public Bxdf
{
public:
    MicrofacetSpecularBxdf(float roughness, Color f0);

    virtual Color f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const override;

private:
    float D(const Vector3& wh) const;
    float ggx_G1(const Vector3& w, const Vector3& n, float alpha) const;
    float ggx_G(const Vector3& wi, const Vector3& wo, const Vector3& n, float alpha) const;

private:
    float roughness_;
    float alpha_;
    Color f0_;//？？？

    float etaI_ = 1.0f;
    float etaT_ = 1.55f;
};

#endif