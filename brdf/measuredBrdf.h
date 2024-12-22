#ifndef _MEASURED_BRDF_H_
#define _MEASURED_BRDF_H_

#include "brdf.h"
#include <powitacq/powitacq_rgb.h>
#include <string>
#include <memory>

class MeasuredBrdf : public Brdf
{
public:
    MeasuredBrdf(const std::string &file);

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const override;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;
    virtual Color get_f(const Vector3 &wo, const Vector3 &wi) const override;

    virtual std::shared_ptr<Brdf> clone() const override;

private:
    std::shared_ptr<powitacq_rgb::BRDF> m_pBrdf;
};

#endif