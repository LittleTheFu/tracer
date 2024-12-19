#include "roughDielectricBsdf.h"

RoughDielectricBsdf::RoughDielectricBsdf(float roughness, float ior)
{
}

Color RoughDielectricBsdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    return Color();
}

Color RoughDielectricBsdf::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color();
}

float RoughDielectricBsdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 0.0f;
}
