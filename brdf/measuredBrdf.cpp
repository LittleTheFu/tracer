#include "measuredBrdf.h"

MeasuredBrdf::MeasuredBrdf()
{
}

Color MeasuredBrdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    return Color();
}

float MeasuredBrdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 0.0f;
}

std::shared_ptr<Brdf> MeasuredBrdf::clone() const
{
    return std::shared_ptr<Brdf>();
}
