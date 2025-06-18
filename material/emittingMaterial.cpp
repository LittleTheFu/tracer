#include "emittingMaterial.h"

bool EmittingMaterial::isEmitting() const
{
    return true;
}

Color EmittingMaterial::getEmittedRadiance() const
{
    return Color::COLOR_WHITE;
}