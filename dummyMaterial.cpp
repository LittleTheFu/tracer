#include "dummyMaterial.h"

Color DummyMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf)
{
    return Color::COLOR_WHITE;
}