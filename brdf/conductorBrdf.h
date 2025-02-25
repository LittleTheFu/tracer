#ifndef _CONDUCTOR_BRDF_H_
#define _CONDUCTOR_BRDF_H_

#include <complex>

#include "brdf.h"
#include "color.h"
#include "microfacet.h"

class ConductorBrdf : public Brdf
{
public:
    ConductorBrdf();
    ConductorBrdf(float eta, float k);

    virtual std::shared_ptr<Brdf> clone() const override;
    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const override;
    virtual Color get_f(const Vector3 &wo, const Vector3 &wi)const override;

private:
    std::complex<float> m_eta;
    Microfacet m_microfacet;
};


#endif