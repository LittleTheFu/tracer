#include "bxdf.h"

Color Bxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    return Color::COLOR_BLACK;
}

Bxdf::Bxdf(BxdfType type)
{
    type_ = type;
};

BxdfType Bxdf::getType() const
{
    return type_;
}

bool Bxdf::isType(BxdfType type) const
{
    return (type_ & type) != 0;
}