#include "materialPlus.h"

std::unique_ptr<Bsdf> MaterialPlus::createBsdf(const Interaction& interaction)
{
    return nullptr;
}

bool MaterialPlus::isEmitting() const
{
    return false;
}

Color MaterialPlus::getEmittedRadiance() const
{
    return Color::COLOR_WHITE;
}

bool MaterialPlus::hasNormalMap() const
{
    return normalTexture_ != nullptr;
}

std::shared_ptr<NormalTexture> MaterialPlus::getNormalTexture() const
{
    return normalTexture_;
}

