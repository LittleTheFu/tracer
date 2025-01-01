#include "common.h"
#include "dielectricMaterial.h"
#include "mathConstantDef.h"
#include "mathUtility.h"

#include <cmath>

DielectricMaterial::DielectricMaterial()
{
    //Warning : don't set it to true,for rough surface is not supported yet...
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
    if (m_isSmooth)
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
    float abs_cos_out = std::abs(wo * normal);

    if (rnd < F)
    {
        m_pCurrentBrdf = m_pMirrorBrdf;
        color = m_pMirrorBrdf->sample_f(wo, wi, pdf) * F;
        if(wi.z != 0.0f)
            color = color / std::abs(wi.z);
        brdf = m_pMirrorBrdf->clone();
        pdf = F;
    }
    else
    {
        m_pCurrentBrdf = m_pGlassBrdf;
        brdf = m_pGlassBrdf->clone();
        color = m_pGlassBrdf->sample_f(wo, wi, pdf) * (1 - F);
        if(wi.z != 0.0f)
            color = color / std::abs(wi.z);
        pdf = 1 - F;
    }

    if (pdf == 0)
    {
        pdf = MathConstant::FLOAT_SMALL_NUMBER;
        // return Color::COLOR_BLACK;
    }

    return color;
}

Color DielectricMaterial::eval_rough(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta, std::shared_ptr<Brdf> &brdf)
{
    isDelta = true;

    Vector3 wm = m_microfacet.sample_wm(wo);
    Vector3 normal = Brdf::LOCAL_NORMAL;

    float cosOut = wo * normal;

    float etaInputSide = m_etaOutside;
    float etaOutputSide = m_etaInside;

    if (cosOut < 0)
    {
        std::swap(etaInputSide, etaOutputSide);
        cosOut = -cosOut;
        normal = -normal;
    }

    float abs_cos_in = std::abs(wo * wm);
    float R = Common::fresnel(etaInputSide, etaOutputSide, abs_cos_in, cosOut);
    float T = 1.0f - R;

    float pr = R;
    float pt = T;

    float rnd = MathUtility::genRandomDecimal();
    Vector3 input_wo = -wo;

    if (rnd < pr)
    {
        Vector3 wi = input_wo.reflect(wm);
        float abs_dot = std::abs(wo * wm);
        pdf = m_microfacet.pdf(wo, wm) / (4 * abs_dot) * pr;
        float f = m_microfacet.d(wo, wm) * m_microfacet.g(wo, wi) * R /
                  (4 * Common::cosTheta(wi) * Common::cosTheta(wo));
        brdf = m_pMirrorBrdf->clone();

        return Color(f, f, f);
    }

    brdf = m_pGlassBrdf->clone();

    // TODO: refraction
    
    bool isTotalReflect = false;
    float fresnel;
    wi = input_wo.refract(wm, etaInputSide, etaOutputSide, isTotalReflect, fresnel);
    float eta_p = etaInputSide / etaOutputSide;

    if(isTotalReflect)
    {
        return Color::COLOR_BLACK;
    }

    float denom = MathUtility::sq(wi * wm + wo * wm / eta_p);
    float dwm_dwi = std::abs(wi * wm) / denom;
    pdf = m_microfacet.pdf(wo, wm) / dwm_dwi * pt;


    float ft = (T * m_microfacet.d(wo, wm) * m_microfacet.g(wo, wi) *
    std::abs((wi * wm) * (wo * wm) /
    (Common::cosTheta(wi) * Common::cosTheta(wo) * denom)));

    return Color(ft, ft, ft);
}
