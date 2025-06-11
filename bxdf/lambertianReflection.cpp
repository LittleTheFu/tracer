#include "lambertianReflection.h"
#include "mathConstantDef.h"

LambertianReflection::LambertianReflection(const Color &reflectance)
{
    reflectance_ = reflectance;
}

Color LambertianReflection::f(const Vector3 &wo, const Vector3 &wi) const
{
    return reflectance_ * MathConstant::INV_PI;
}

float LambertianReflection::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return MathConstant::INV_TWO_PI;
}

Color LambertianReflection::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    wi = Vector3::sampleUniformFromHemisphere();
    pdf = MathConstant::INV_TWO_PI;

    return reflectance_ * MathConstant::INV_PI;
}