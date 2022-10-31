#include "lambertian.h"
#include "common.h"
#include <cmath>
#include <algorithm>

Lambertian::Lambertian(Color rho)
{
    m_rho = rho;
}

Color Lambertian::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf)
{
    wi = Vector3::sampleUniformFromHemisphere();
    pdf = Common::INV_TWO_PI;

    return m_rho * Common::INV_PI;
}

Color Lambertian::calc(const Color &inputColor, const Vector3 &wi, float pdf)
{
    // float dot = std::clamp(wi * Common::LOCAL_NORMAL, 0.0f, 1.0f);
    
    return Color::COLOR_WHITE;
}