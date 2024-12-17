#include "conductorBrdf.h"

ConductorBrdf::ConductorBrdf(float etaOutside, float etaInside, float k)
{
}

std::shared_ptr<Brdf> ConductorBrdf::clone() const
{
    return std::shared_ptr<Brdf>();
}

Color ConductorBrdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    return Color();
}

Color ConductorBrdf::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color();
}
