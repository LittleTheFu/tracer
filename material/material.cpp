#include "material.h"

Material::Material()
{
}

Color Material::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_WHITE;
}

Color Material::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta) const
{
    return Color::COLOR_BLACK;
}