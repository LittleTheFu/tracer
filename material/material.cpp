#include "material.h"

Material::Material()
{
}

Color Material::eval(float u,
                     float v,
                     const Vector3 &wo,
                     Vector3 &wi,
                     float &pdf,
                     bool &isDelta,
                     std::shared_ptr<Brdf> &brdf)
{
    return Color::COLOR_BLACK;
}