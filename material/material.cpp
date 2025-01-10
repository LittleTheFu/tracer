#include "material.h"

Material::Material()
{
    m_NormalTexture = nullptr;
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

void Material::setNormalTexture(std::shared_ptr<NormalTexture> normalTexture)
{
    m_NormalTexture = normalTexture;
}

bool Material::isNormalTextureValid() const
{
    return m_NormalTexture != nullptr;
}

std::shared_ptr<NormalTexture> Material::getNormalTexture() const
{
    return m_NormalTexture;
}
