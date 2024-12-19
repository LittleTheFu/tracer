#include "mirrorMaterial.h"
#include "mirror.h"

MirrorMaterial::MirrorMaterial()
{
    m_pMirrorBrdf = new Mirror();
}

Color MirrorMaterial::eval(float u,
                           float v,
                           const Vector3 &wo,
                           Vector3 &wi,
                           float &pdf,
                           bool &isDelta,
                           std::shared_ptr<Brdf> &brdf)
{
    isDelta = true;
    Color color = m_pMirrorBrdf->sample_f(wo, wi, pdf);
    brdf = m_pMirrorBrdf->clone();

    return color;
}