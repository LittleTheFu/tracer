#include "specularBxdf.h"
#include <cassert>

SpecularBxdf::SpecularBxdf()
    : Bxdf(static_cast<BxdfType>(BxdfType::REFLECTION | BxdfType::SPECULAR))
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
    // Vector3 n = interaction.normal_shading;
    Vector3 n = Vector3(0, 0, 1);

    if(!wo.isSameDir(n))
    {
        assert(0);
        wi = Vector3::ZERO;
        pdf = 0;

        return Color::COLOR_BLACK;
    }

    wi = (-wo).reflect(n);
    pdf = 1;

    return Color::COLOR_WHITE;
}