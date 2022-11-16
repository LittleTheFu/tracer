#include "material.h"

Material::Material()
{
}

Color Material::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    return Color::COLOR_BLACK;
}

bool Material::isMirror() const
{
    return false;
}