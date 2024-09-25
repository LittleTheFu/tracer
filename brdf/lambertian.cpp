#include "lambertian.h"
#include "common.h"
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
    return m_color * Common::INV_PI * m_scale;
}

Color Lambertian::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    wi = Vector3::sampleUniformFromHemisphere();
    pdf = Common::INV_TWO_PI;

    return m_color * Common::INV_PI * m_scale;
}