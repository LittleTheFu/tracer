#include "lambertian.h"
#include "mathConstantDef.h"
#include <cmath>
#include <algorithm>

Lambertian::Lambertian(float scale)
{
    m_color = Color::COLOR_BLACK;
    m_scale = scale;
}

void Lambertian::setColor(const Color &rho)
{
    m_color = rho;
}

Color Lambertian::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return m_color * MathConstant::INV_PI * m_scale;
}

Color Lambertian::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
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