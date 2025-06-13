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
    return Color::COLOR_BLACK;
}