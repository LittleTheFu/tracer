#ifndef _GLASS_H_
#define _GLASS_H_

#include "brdf.h"

class Glass : public Brdf
{
public:
    Glass(float etaOutsie, float etaInside);

    Color get_f(const Vector3 &wo, const Vector3 &wi) const override;

    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;

private:
    float m_etaOutside;
    float m_etaInside;
};

#endif