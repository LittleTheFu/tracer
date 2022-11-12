#include "material.h"

Material::Material()
{
    pBrdf = nullptr;
    pTexture = nullptr;
}

Color Material::calc(const Color &inputColor, const Ray &inputDir) const
{
    return Color::COLOR_WHITE;
}