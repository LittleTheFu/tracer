#include "measuredMaterial.h"
#include "resourceDef.h"

MeasuredMaterial::MeasuredMaterial(const std::string &brdfPath)
{
    m_brdf = std::make_shared<MeasuredBrdf>(brdfPath);
}

Color MeasuredMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta, std::shared_ptr<Brdf> &brdf)
{
    isDelta = false;
    brdf = m_brdf->clone();

    return m_brdf->sample_f(wo, wi, pdf);
}
