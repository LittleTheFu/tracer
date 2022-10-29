#include "lambertian.h"
#include "common.h"

Lambertian::Lambertian(float rho)
{
    m_rho = rho;
}

float Lambertian::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf)
{
    wi = Vector3::sampleUniformFromHemisphere();
    pdf = Common::INV_TWO_PI;
    
    return m_rho * Common::INV_PI;
}
