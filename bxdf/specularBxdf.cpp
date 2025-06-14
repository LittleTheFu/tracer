#include "specularBxdf.h"

SpecularBxdf::SpecularBxdf()
    : Bxdf(BxdfType::REFLECTION)
{
}

Color SpecularBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_BLACK;
}

float SpecularBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 0;
}

Color SpecularBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    // const Vector3 local_wo = -wo;
    Vector3 n = interaction.normal_shading;

    if(!wo.isSameDir(n))
    {
        wi = Vector3::ZERO;
        pdf = 0;

        return Color::COLOR_BLACK;
    }

    wi = (-wo).reflect(n);
    pdf = 1;

    return Color::COLOR_WHITE;
}