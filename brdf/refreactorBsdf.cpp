#include <algorithm>
#include <cassert>

#include "mathUtility.h"
#include "color.h"
#include "refreactorBsdf.h"

RefrectorBsdf::RefrectorBsdf(float etaOutsie, float etaInside)
{
    assert(etaInside != 0);
    assert(etaOutsie != 0);

    m_etaInside = etaInside;
    m_etaOutside = etaOutsie;
}

Color RefrectorBsdf::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_BLACK;
}

Color RefrectorBsdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    Vector3 normal = LOCAL_NORMAL;
    float dot = wo * normal;

    float etaInputSide = m_etaOutside;
    float etaOutputSide = m_etaInside;

    if (dot < 0)
    {
        normal = -normal;
        std::swap(etaInputSide, etaOutputSide);
    }

    // Vector3 inputVector = Vector3(wo.x, wo.y, -wo.z);
    Vector3 inputVector = -wo;
    bool totalReflect;
    float fresnel;
    wi = inputVector.refract(normal, etaInputSide, etaOutputSide, totalReflect, fresnel);

    pdf = 1;

    //for debug
    // if(totalReflect)
    // {
    //     return Color::COLOR_BLACK;
    // }
    // else
    // {
    //     return Color::COLOR_WHITE;
    // }

    return Color::COLOR_WHITE * MathUtility::sq(etaOutputSide / etaInputSide);
}

float RefrectorBsdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 0.0f;
}

std::shared_ptr<Brdf> RefrectorBsdf::clone() const
{
    return std::make_shared<RefrectorBsdf>(*this);
}
