#include "conductorMaterial.h"

ConductorMaterial::ConductorMaterial()
{
}

Color ConductorMaterial::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color();
}

Color ConductorMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta, std::shared_ptr<Brdf> &brdf)
{
    return Color();
}
