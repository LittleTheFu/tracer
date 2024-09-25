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

Color MixMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    float etaOutside = m_etaOutside;
    float etaInside = m_etaInside;
    Vector3 normal = Brdf::LOCAL_NORMAL;

    float cosOut = wo * normal;

    if (cosOut < 0)
    {
        std::swap(etaInside, etaOutside);
        cosOut = -cosOut;
        normal = -normal;
    }

    bool totalReflect = false;
    Vector3 inputVector = -wo;
    Vector3 refractVector = inputVector.refract(normal, etaOutside, etaInside, totalReflect);
    float F = 1;
    if (!totalReflect)
    {
        float sinOut = std::sqrt(1 - cosOut * cosOut);
        float sinIn = sinOut * etaOutside / etaInside;
        float cosIn = std::sqrt(1 - sinIn * sinIn);

        float r_pa = (etaInside * cosOut - etaOutside * cosIn) / (etaInside * cosOut + etaOutside * cosIn);
        float r_per = (etaOutside * cosOut - etaInside * cosIn) / (etaOutside * cosOut + etaInside * cosIn);

        F = 0.5 * (r_pa * r_pa + r_per * r_per);
    }

    float rnd = Common::genRandomDecimal();

    Color color;

    if (rnd < F)
    {
        color = m_pMirrorBrdf->sample_f(wo, wi, pdf) * F;
        pdf = F;
    }
    else
    {
        color = m_pGlassBrdf->sample_f(wo, wi, pdf) * (1 - F);
        pdf = 1 - F;
    }

    if(pdf == 0)
    {
        pdf = Common::FLOAT_SAMLL_NUMBER;
    }

    return color;
}