#include "material.h"

Material::Material()
{
    r = 0;
    g = 0;
    b = 0;
    a = 255;

    specular = false;
}

Material::Material(unsigned char r, unsigned char g, unsigned char b)
{
    a = 255;
    set(r, g, b);

    specular = false;
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

void Material::safeAdd(const Material &that)
{
    unsigned char t_r = r + that.r;
    unsigned char t_g = g + that.g;
    unsigned char t_b = b + that.b;

    if (t_r < r || t_r < that.r)
        t_r = 255;

    if (t_g < g || t_g < that.g)
        t_g = 255;

    if (t_b < b || t_b < that.b)
        t_b = 255;

    r = t_r;
    g = t_g;
    b = t_b;
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

Material Material::operator*(const Material &that) const
{
    float factor_r = that.r / 255.0f;
    float factor_g = that.g / 255.0f;
    float factor_b = that.b / 255.0f;

    unsigned char r = this->r * factor_r;
    unsigned char g = this->g * factor_g;
    unsigned char b = this->b * factor_b;

    return Material(r, g, b);
}

Material Material::operator+(const Material &that) const
{
    unsigned char t_r = r + that.r;
    unsigned char t_g = g + that.g;
    unsigned char t_b = b + that.b;

    if (t_r < r || t_r < that.r)
        t_r = 255;

    if (t_g < g || t_g < that.g)
        t_g = 255;

    if (t_b < b || t_b < that.b)
        t_b = 255;

    return Material(t_r, t_g, t_b);
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