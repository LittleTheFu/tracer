#include "glassMaterial.h"
#include "glass.h"

GlassMaterial::GlassMaterial()
{
    m_pGlassBrdf = new Glass(1, 1.5);
}

bool GlassMaterial::isMirror() const
{
    return true;
}

bool GlassMaterial::isDelta() const
{
    return true;
}

Color GlassMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    Color color = m_pGlassBrdf->sample_f(wo, wi, pdf);

    return color;
}