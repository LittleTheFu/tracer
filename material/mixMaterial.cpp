#include "mixMaterial.h"
#include "common.h"
#include <cmath>

MixMaterial::MixMaterial()
{
    m_etaOutside = 1;
    m_etaInside = 1.5;

    m_pGlassBrdf = new Glass(m_etaOutside, m_etaInside);
    m_pMirrorBrdf = new Mirror();
}

bool MixMaterial::isMirror() const
{
    return true;
}

bool MixMaterial::isDelta() const
{
    return true;
}

Color MixMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    float etaInputSide = m_etaOutside;
    float etaOutputSide = m_etaInside;
    Vector3 normal = Brdf::LOCAL_NORMAL;

    float cosOut = wo * normal;

    if (cosOut < 0)
    {
        std::swap(etaInputSide, etaOutputSide);
        cosOut = -cosOut;
        normal = -normal;
    }

    bool totalReflect = false;
    Vector3 inputVector = -wo;
    float fresnel;
    Vector3 refractVector = inputVector._refract(normal, etaInputSide, etaOutputSide, totalReflect, fresnel);
    float F = 1;
    if (!totalReflect)
    {
        F = fresnel;
    }

    float rnd = Common::genRandomDecimal();

    Color color;

    if (rnd < F)
    {
        color = m_pMirrorBrdf->sample_f(wo, wi, pdf);
        pdf = F;
    }
    else
    {
        color = m_pGlassBrdf->sample_f(wo, wi, pdf);
        pdf = 1 - F;
    }

    if(pdf == 0)
    {
        pdf = Common::FLOAT_SAMLL_NUMBER;
        // return Color::COLOR_BLACK;
    }

    return color;
}