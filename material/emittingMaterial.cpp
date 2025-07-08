#include "emittingMaterial.h"

bool EmittingMaterial::isEmitting() const
{
    return true;
}

void EmittingMaterial::setEmittedRadiance(const Color &radiance)
{
}

Color EmittingMaterial::getEmittedRadiance() const
{
    return Color::COLOR_WHITE;
}