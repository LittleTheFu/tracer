#include "material.h"

Material::Material()
{
    r = 0;
    g = 0;
    b = 0;
    a = 255;
}

Material::Material(unsigned char r, unsigned char g, unsigned char b)
{
    a = 255;
    set(r, g, b);
}

void Material::set(unsigned char r, unsigned char g, unsigned char b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void Material::set(const Material &mtrl)
{
    (*this) = mtrl;
}

Material &Material::operator+=(const Material &that)
{
    r += that.r;
    g += that.g;
    b += that.b;

    return *this;
}

Material Material::operator*(float m)
{
    return Material(r * m, g * m, b * m);
}

Material &Material::operator*=(float m)
{
    r *= m;
    g *= m;
    b *= m;

    return *this;
}

const Material Material::MTRL_RED = Material(255, 0, 0);
const Material Material::MTRL_GREEN = Material(0, 255, 0);
const Material Material::MTRL_BLUE = Material(0, 0, 255);
const Material Material::MTRL_YELLOW = Material(255, 255, 0);
const Material Material::MTRL_AQUA = Material(0, 255, 255);
const Material Material::MTRL_SILVER = Material(192, 192, 192);
const Material Material::MTRL_GRAY = Material(128, 128, 128);
const Material Material::MTRL_PURPLE = Material(128, 0, 128);
const Material Material::MTRL_WHITE = Material(255, 255, 255);
const Material Material::MTRL_BLACK = Material(0, 0, 0);