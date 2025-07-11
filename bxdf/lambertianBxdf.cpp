#include "lambertianBxdf.h"
#include "mathConstantDef.h"

LambertianBxdf::LambertianBxdf(const Color &reflectance)
    : Bxdf(BxdfType::DIFFUSE)
{
    reflectance_ = reflectance;
}

Color LambertianBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    return reflectance_ * MathConstant::INV_PI;
}

float LambertianBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    float cosTheta = wi.z;
    if (cosTheta < MathConstant::FLOAT_SMALL_NUMBER)
    {
        return 0.0f;
    }

    return cosTheta * MathConstant::INV_PI;
}

Color LambertianBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    wi = Vector3::sampleUniformFromHemisphere();

    pdf = wi.z * MathConstant::INV_PI; // cos(theta) / PI

    if (pdf < MathConstant::FLOAT_SMALL_NUMBER)
    {
        pdf = 0.0f;
        return Color::COLOR_BLACK;
    }

    return reflectance_ * MathConstant::INV_PI;
}