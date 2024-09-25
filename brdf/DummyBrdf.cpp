#include "DummyBrdf.h"
#include "color.h"
#include "vector.h"

Color DummyBrdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf)
{
    pdf = 1;
    wi = Vector3::ZERO;
    
    return Color::COLOR_WHITE;
}