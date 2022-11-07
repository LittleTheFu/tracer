#include "glass.h"
#include "color.h"

Glass::Glass()
{
}

Color Glass::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf)
{
    return Color::COLOR_WHITE;
}

bool Glass::isGlass() const
{
    return true;
}