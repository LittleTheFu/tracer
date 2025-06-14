#ifndef _MEASURED_BXDF_H_
#define _MEASURED_BXDF_H_

#include "bxdf.h"
#include <powitacq/powitacq_rgb.h>


class MeasuredBxdf : public Bxdf
{
public:
    MeasuredBxdf(const std::string &file);

    virtual Color f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const override;

private:
    std::shared_ptr<powitacq_rgb::BRDF> brdf_;
};
#endif