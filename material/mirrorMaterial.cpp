#include "mirrorMaterial.h"
#include "mirror.h"

MirrorMaterial::MirrorMaterial()
{
    m_pMirrorBrdf = new Mirror();
}

Color MirrorMaterial::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return m_pMirrorBrdf->get_f(wo, wi);
}

Color MirrorMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta)
{
    isDelta = true;
    Color color = m_pMirrorBrdf->sample_f(wo, wi, pdf);

    return color;
}