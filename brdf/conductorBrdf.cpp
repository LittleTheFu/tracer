#include "conductorBrdf.h"
#include "common.h"

ConductorBrdf::ConductorBrdf()
{
    m_eta = std::complex<float>(2.4f, 3.5f);
}

ConductorBrdf::ConductorBrdf(float eta, float k)
{
    m_eta.real(eta);
    m_eta.imag(k);
}

std::shared_ptr<Brdf> ConductorBrdf::clone() const
{
    return std::make_shared<ConductorBrdf>(*this);
}

Color ConductorBrdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    const Vector3 local_wo = -wo;

    Vector3 n = LOCAL_NORMAL;
    if (local_wo.isSameDir(n))
    {
        wi = Vector3::ZERO;
        pdf = 1;
        return Color::COLOR_BLACK;
    }

    Vector3 wm = m_microfacet.sample_wm(wo);
    wi = local_wo.reflect(wm);

    pdf = m_microfacet.pdf(wo, wi);

    float absCosTheta_o = Common::absCosTheta(wo);
    float absCosTheta_i = Common::absCosTheta(wi);

    float absDot = std::abs(wo * wi);

    float f = Common::frenselComplex(m_eta, absDot);

    wm.normalize();

    float final_f = m_microfacet.distribution(wm) * f * m_microfacet.g(wo, wi) / (4 * absCosTheta_o * absCosTheta_i);

    Color F(final_f, final_f, final_f);

    return F;
}

Color ConductorBrdf::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    float absDot = std::abs(wo * wi);

    float f = Common::frenselComplex(m_eta, absDot);

    Vector3 wm = wo + wi;
    wm.normalize();

    float absCosTheta_o = Common::absCosTheta(wo);
    float absCosTheta_i = Common::absCosTheta(wi);

    float final_f = m_microfacet.distribution(wm) * f * m_microfacet.g(wo, wi) / (4 * absCosTheta_o * absCosTheta_i);

    Color F(final_f, final_f, final_f);

    return F;
}
