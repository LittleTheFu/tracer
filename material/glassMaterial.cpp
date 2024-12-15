#include "glassMaterial.h"
#include "glass.h"

GlassMaterial::GlassMaterial()
{
    m_pGlassBrdf = new Glass(1, 1.5);
}

Color GlassMaterial::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return m_pGlassBrdf->get_f(wo, wi);
}

Color GlassMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta)
{
    isDelta = true;
    Color color = m_pGlassBrdf->sample_f(wo, wi, pdf);

    return color;
}