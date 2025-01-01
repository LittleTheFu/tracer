#include "refreactorMaterial.h"
#include "refreactorBsdf.h"

RefreactorMaterial::RefreactorMaterial()
{
    m_pRefreactorBsdf = new RefrectorBsdf(1, 1.5);
}

Color RefreactorMaterial::eval(float u,
                          float v,
                          const Vector3 &wo,
                          Vector3 &wi,
                          float &pdf,
                          bool &isDelta,
                          std::shared_ptr<Brdf> &brdf)
{
    isDelta = true;
    Color color = m_pRefreactorBsdf->sample_f(wo, wi, pdf);
    brdf = m_pRefreactorBsdf->clone();

    return color;
}