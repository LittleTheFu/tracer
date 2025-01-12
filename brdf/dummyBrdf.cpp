#include "dummyBrdf.h"
#include "color.h"
#include "vector.h"

Color DummyBrdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    pdf = 1;
    wi = Vector3::ZERO;
    
    return Color::COLOR_WHITE;
}
std::shared_ptr<Brdf> DummyBrdf::clone() const
{
    return std::make_shared<DummyBrdf>();
}
