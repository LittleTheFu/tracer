#ifndef _MEASURED_BRDF_H_
#define _MEASURED_BRDF_H_

#include "brdf.h"

class MeasuredBrdf : public Brdf
{
public:
    MeasuredBrdf();

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const override;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;

    virtual std::shared_ptr<Brdf> clone() const override;
};

#endif