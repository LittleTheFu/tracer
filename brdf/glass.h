#ifndef _GLASS_H_
#define _GLASS_H_

#include "brdf.h"

class Glass : public Brdf
{
public:
    Glass(float etaOutsie, float etaInside);

    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const;
    bool isGlass() const;

private:
    float m_etaOutside;
    float m_etaInside;
};

#endif