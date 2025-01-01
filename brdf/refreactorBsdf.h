#ifndef _REFREACTOR_BSDF_H_
#define _REFREACTOR_BSDF_H_

#include "brdf.h"

class RefrectorBsdf : public Brdf
{
public:
    RefrectorBsdf(float etaOutsie, float etaInside);

    Color get_f(const Vector3 &wo, const Vector3 &wi) const override;

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const override;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;
    virtual std::shared_ptr<Brdf> clone() const override;

private:
    float m_etaOutside;
    float m_etaInside;
};

#endif