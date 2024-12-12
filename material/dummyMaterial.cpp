#include "dummyMaterial.h"

Color DummyMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta)
{
    return Color::COLOR_WHITE;
}