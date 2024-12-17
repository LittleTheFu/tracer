#ifndef _CONDUCTOR_BRDF_H_
#define _CONDUCTOR_BRDF_H_

#include "brdf.h"
#include "color.h"

class ConductorBrdf : public Brdf
{
public:
    ConductorBrdf(float etaOutside, float etaInside, float k);

    virtual std::shared_ptr<Brdf> clone() const override;
    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const override;
    virtual Color get_f(const Vector3 &wo, const Vector3 &wi)const override;
};


#endif