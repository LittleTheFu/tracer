#include "brdf.h"

const Vector3 Brdf::LOCAL_NORMAL = Vector3(0, 0, 1);

Color Brdf::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_WHITE;
}

bool Brdf::isGlass() const
{
    return false;
}

float Brdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 1.0f;
}
