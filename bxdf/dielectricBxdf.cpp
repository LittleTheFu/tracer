#include "dielectricBxdf.h"
#include <mathUtility.h>
#include <cassert>

DielectricBxdf::DielectricBxdf(float etaI, float etaT)
    : Bxdf(static_cast<BxdfType>(BxdfType::SPECULAR | BxdfType::REFLECTION | BxdfType::TRANSMISSION))
{
    etaI_ = etaI;
    etaT_ = etaT;
}

Color DielectricBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_BLACK;
}

float DielectricBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 0.0f;
}

Color DielectricBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    Vector3 normal = Vector3(0, 0, 1);
    float dot = wo * normal;

    float etaI = etaI_;
    float etaT = etaT_;

    if (dot < 0)
    {
        normal = -normal;
        // std::swap(etaI, etaT);
    }

    // Vector3 inputVector = Vector3(wo.x, wo.y, -wo.z);
    Vector3 inputVector = -wo;
    bool totalReflect;
    float fresnel;
    wi = inputVector.refract(normal, etaI, etaT, totalReflect, fresnel);

    assert(MathUtility::is_in_range(fresnel, 0.0f, 1 + 0.00001f, true, true));
    
    pdf = fresnel;

    //for debug
    // if(totalReflect)
    // {
    //     return Color::COLOR_BLACK;
    // }
    // else
    // {
    //     return Color::COLOR_WHITE;
    // }

    return Color::COLOR_WHITE * MathUtility::sq(etaT / etaI);
    // return Color::COLOR_WHITE;
}
