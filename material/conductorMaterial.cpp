#include "conductorMaterial.h"

ConductorMaterial::ConductorMaterial()
{
    m_pConductorBrdf = std::make_shared<ConductorBrdf>();
}

Color ConductorMaterial::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return m_pConductorBrdf->get_f(wo, wi);
}

Color ConductorMaterial::eval(float u,
                              float v,
                              const Vector3 &wo,
                              Vector3 &wi,
                              float &pdf,
                              bool &isDelta,
                              std::shared_ptr<Brdf> &brdf)
{
    isDelta = false;
    brdf = m_pConductorBrdf->clone();

    Color f = m_pConductorBrdf->sample_f(wo, wi, pdf);

    return f;
}
