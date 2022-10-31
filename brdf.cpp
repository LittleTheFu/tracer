#include "brdf.h"

const Vector3 Brdf::LOCAL_NORMAL = Vector3(0, 0, 1);

Color Brdf::calc(const Color &inputColor, const Vector3 &wi, float pdf)
{
    return Color::COLOR_BLUE;
}