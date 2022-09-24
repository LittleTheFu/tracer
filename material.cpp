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
    set(r, g, b);
}

void Material::set(unsigned char r, unsigned char g, unsigned char b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

const Material Material::MTRL_1 = Material(25,10,10);
const Material Material::MTRL_2 = Material(10,10,10);
const Material Material::MTRL_3 = Material(10,10,10);
const Material Material::MTRL_4 = Material(10,10,10);
const Material Material::MTRL_5 = Material(10,10,10);
const Material Material::MTRL_6 = Material(10,10,10);
const Material Material::MTRL_7 = Material(10,10,10);
const Material Material::MTRL_8 = Material(10,10,10);
const Material Material::MTRL_9 = Material(10,10,10);
const Material Material::MTRL_10 = Material(10,10,10);