#include "conductorBrdf.h"
#include "common.h"

ConductorBrdf::ConductorBrdf(float eta, float k)
{
    m_eta.real(eta);
    m_eta.imag(k);
}

std::shared_ptr<Brdf> ConductorBrdf::clone() const
{
    return std::shared_ptr<Brdf>();
}

Color ConductorBrdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    const Vector3 local_wo = -wo;
    
    Vector3 n = LOCAL_NORMAL;
    if(local_wo.isSameDir(n))
    {
        wi = Vector3::ZERO;
        pdf = 1;
        return Color::COLOR_BLACK;
        
        n = -n;
    }

    wi = local_wo.reflect(n);
    float absCosTheta = Common::absCosTheta(wi);

    float f = Common::frenselComplex(m_eta, absCosTheta);
    Color cf(f, f, f);

    return cf;
}

Color ConductorBrdf::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_BLACK;
}
