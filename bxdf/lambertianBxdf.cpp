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
    return MathConstant::INV_TWO_PI;
}

Color LambertianBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    wi = Vector3::sampleUniformFromHemisphere();
    pdf = MathConstant::INV_TWO_PI;

    return reflectance_ * MathConstant::INV_PI;
}