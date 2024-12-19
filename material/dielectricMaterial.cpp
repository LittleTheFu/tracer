#include "dielectricMaterial.h"
#include "mathUtility.h"
#include "mathConstantDef.h"
#include <cmath>

DielectricMaterial::DielectricMaterial()
{
    m_isSmooth = true;

    m_etaOutside = 1;
    m_etaInside = 1.5;

    m_pGlassBrdf = new Glass(m_etaOutside, m_etaInside);
    m_pMirrorBrdf = new Mirror();

    m_pCurrentBrdf = m_pGlassBrdf;
}

Color DielectricMaterial::eval(float u,
                               float v,
                               const Vector3 &wo,
                               Vector3 &wi,
                               float &pdf,
                               bool &isDelta,
                               std::shared_ptr<Brdf> &brdf)
{
    if(m_isSmooth)
        return eval_smooth(u, v, wo, wi, pdf, isDelta, brdf);

    return eval_rough(u, v, wo, wi, pdf, isDelta, brdf);
}

Color DielectricMaterial::eval_smooth(float u,
                               float v,
                               const Vector3 &wo,
                               Vector3 &wi,
                               float &pdf,
                               bool &isDelta,
                               std::shared_ptr<Brdf> &brdf)
{
    isDelta = true;
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
    Vector3 refractVector = inputVector.refract(normal, etaInputSide, etaOutputSide, totalReflect, fresnel);
    float F = 1;
    if (!totalReflect)
    {
        F = fresnel;
    }

    float rnd = MathUtility::genRandomDecimal();

    Color color;

    if (rnd < F)
    {
        m_pCurrentBrdf = m_pMirrorBrdf;
        color = m_pMirrorBrdf->sample_f(wo, wi, pdf);
        brdf = m_pMirrorBrdf->clone();
        pdf = F;
    }
    else
    {
        m_pCurrentBrdf = m_pGlassBrdf;
        brdf = m_pGlassBrdf->clone();
        color = m_pGlassBrdf->sample_f(wo, wi, pdf);
        pdf = 1 - F;
    }

    if(pdf == 0)
    {
        pdf = MathConstant::FLOAT_SAMLL_NUMBER;
        // return Color::COLOR_BLACK;
    }

    return color;
}

Color DielectricMaterial::eval_rough(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta, std::shared_ptr<Brdf> &brdf)
{
    return Color();
}
