#include "material.h"

std::unique_ptr<Bsdf> Material::createBsdf(const Interaction& interaction)
{
    return nullptr;
}

bool Material::isEmitting() const
{
    return false;
}

Color Material::getEmittedRadiance() const
{
    return Color::COLOR_WHITE;
}

bool Material::hasNormalMap() const
{
    return normalTexture_ != nullptr;
}

std::shared_ptr<NormalTexture> Material::getNormalTexture() const
{
    return normalTexture_;
}

void Material::setNormalTexture(std::shared_ptr<NormalTexture> normalTexture)
{
    normalTexture_ = normalTexture;
}

