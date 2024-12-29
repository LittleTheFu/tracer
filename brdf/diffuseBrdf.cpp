#include <algorithm>
#include <cmath>

#include "diffuseBrdf.h"
#include "mathConstantDef.h"

DiffuseBrdf::DiffuseBrdf(float scale)
{
    m_color = Color::COLOR_BLACK;
    m_scale = scale;
}

void DiffuseBrdf::setColor(const Color &rho)
{
    m_color = rho;
}

float DiffuseBrdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return MathConstant::INV_TWO_PI;
}

std::shared_ptr<Brdf> DiffuseBrdf::clone() const
{
    return std::make_shared<DiffuseBrdf>(*this);
}

Color DiffuseBrdf::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return m_color * MathConstant::INV_PI * m_scale;
}

Color DiffuseBrdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    float z = wo.z;
    // if(z < 0)
    // {
    //     wi = Vector3::ZERO;
    //     pdf = 1;
    //     return Color::COLOR_BLACK;
    // }
    wi = Vector3::sampleUniformFromHemisphere();
    pdf = MathConstant::INV_TWO_PI;

    return m_color * MathConstant::INV_PI * m_scale;
}