#include "lambertian.h"
#include "common/common.h"
#include <cmath>
#include <algorithm>

Lambertian::Lambertian(float scale)
{
    m_rho = Color::COLOR_BLACK;
    m_scale = scale;
}

Lambertian::Lambertian(const Color &rho, float scale)
{
    m_rho = rho;
    m_scale = scale;
}

void Lambertian::setRho(const Color &rho)
{
    m_rho = rho;
}

Color Lambertian::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    wi = Vector3::sampleUniformFromHemisphere();
    pdf = Common::INV_TWO_PI;

    return m_rho * Common::INV_PI * m_scale;
}