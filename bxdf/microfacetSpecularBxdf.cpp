#include "microfacetSpecularBxdf.h"
#include "mathConstantDef.h"
#include <common.h>

MicrofacetSpecularBxdf::MicrofacetSpecularBxdf(float roughness)
    : Bxdf(BxdfType::REFLECTION | BxdfType::GLOSSY)
{
    roughness_ = roughness;
    alpha_ = roughness * roughness;

    if (alpha_ <= 0)
        alpha_ = MathConstant::FLOAT_SMALL_NUMBER;
}

Color MicrofacetSpecularBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    if(wo.z <= 0 || wi.z <= 0)
        return Color::COLOR_BLACK;

    Vector3 wh = (wo + wi).dir();

    bool totalReflect = false;
    float f;
    Vector3 wt = wi.refract(wh, etaI_, etaT_, totalReflect, f);
    if(totalReflect)
    {
        f = 1.0f;
    }

    float d = D(wh);
    float g = ggx_G(wi, wo, Vector3(0,0,1), alpha_);

    return Color(d * g * f / (4.0f * wo.z * wi.z));
}

float MicrofacetSpecularBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    if(wo.z <= 0 || wi.z <= 0)
        return 0.0f;

    Vector3 wh = (wo + wi).dir();
    
    if(wh.isZero() || wh.z <= 0)
        return 0.0f;

    float d_val = D(wh);
    float NdotH = std::abs(wh.z);
    float HdotI = std::abs(wh * wi);

    const float EPSILON = MathConstant::FLOAT_SMALL_NUMBER;
    float denominator = 4.0f * HdotI;

    if (denominator < EPSILON) {
        return 0.0f;
    }

    float pdf_val = (d_val * NdotH) / denominator;

    return pdf_val;
}

Color MicrofacetSpecularBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
}

float MicrofacetSpecularBxdf::D(const Vector3 &wh) const
{
    if(wh.z < 0)
        return 0.0f;

    float alpha2 = alpha_ * alpha_;
    float z2 = wh.z * wh.z;
    float denominator_term = z2 * (alpha2 - 1.0f) + 1.0f;

    float denominator_term = z2 * (alpha2 - 1.0f) + 1.0f;
    float denominator = MathConstant::PI * denominator_term * denominator_term;

    if (denominator == 0.0f) {
        return 0.0f;
    }

    return alpha2 / denominator;
}

float MicrofacetSpecularBxdf::ggx_G1(const Vector3& w, const Vector3& n, float alpha) const
{
    float z = n * w;

    if (z <= 0.0f) {
        return 0.0f;
    }

    float alpha2 = alpha * alpha;
    float z2 = z * z;

    float sqrt_term = std::sqrt(alpha2 + (1.0f - alpha2) * z2);

    return (2.0f * z) / (z + sqrt_term);
}

float MicrofacetSpecularBxdf::ggx_G(const Vector3& wi, const Vector3& wo, const Vector3& n, float alpha) const
{
    return ggx_G1(wi, n, alpha) * ggx_G1(wo, n, alpha);
}
