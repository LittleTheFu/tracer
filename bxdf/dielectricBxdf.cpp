#include "dielectricBxdf.h"

DielectricBxdf::DielectricBxdf(float ior)
    : Bxdf(BxdfType::REFLECTION | BxdfType::TRANSMISSION)
{
    ior_ = ior;
}

Color DielectricBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_WHITE;
}

float DielectricBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 1.0f;
}

Color DielectricBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    return Color::COLOR_WHITE;
}
