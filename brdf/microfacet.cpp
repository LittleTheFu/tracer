#include "microfacet.h"
#include "common.h"
#include "mathUtility.h"
#include "mathConstantDef.h"
#include "frame.h"

Microfacet::Microfacet()
{
    m_alpha_x = 1.0f;
    m_alpha_y = 1.0f;
}

Microfacet::Microfacet(float alpha_x, float alpha_y)
{
    m_alpha_x = alpha_x;
    m_alpha_y = alpha_y;
}

float Microfacet::distribution(const Vector3 &wm) const
{
    float tanThetaSq = Common::tanThetaSq(wm);
    float e = Common::cosPhiSq(wm) / m_alpha_x + Common::sinPhiSq(wm) / m_alpha_y;
    float f = MathUtility::sq(1.0f + tanThetaSq * e);

    float alpha = m_alpha_x * m_alpha_y;
    float cosThetaSqSq = MathUtility::sq(Common::cosThetaSq(wm));
    float g = MathConstant::PI * alpha * cosThetaSqSq * f;

    // it's easier to debug if the return value is written like this
    float r = 1.0f / g;

    return r;
}

bool Microfacet::isSmooth() const
{
    return std::max(m_alpha_x, m_alpha_y) < MathConstant::FLOAT_SAMLL_NUMBER;
}

float Microfacet::lambda(const Vector3 &w) const
{
    float tan2Theta = Common::tanThetaSq(w);

    if (std::isfinite(tan2Theta))
        return 0.0f;

    float alpha2 = MathUtility::sq(m_alpha_x * Common::cosPhi(w)) +
                   MathUtility::sq(m_alpha_y * Common::sinPhi(w));

    float r = (std::sqrt(1.0f + alpha2 * tan2Theta) - 1.0f) / 2.0f;

    return r;
}

float Microfacet::g(const Vector3 &wo, const Vector3 &wi) const
{
    float r = 1.0f / (1.0f + lambda(wo) + lambda(wi));

    return r;
}

float Microfacet::g1(const Vector3 &w) const
{
    float r = 1.0f / (1.0f + lambda(w));

    return r;
}

float Microfacet::d(const Vector3 &w, const Vector3 &wm) const
{
    float absCosTheta = std::abs(Common::cosTheta(wm));
    float absDot = std::abs(w * wm);

    float r = g1(w) / absCosTheta * distribution(wm) * absDot;

    return r;
}

Vector3 Microfacet::sample_wm(const Vector3 &w) const
{
    Vector3 wh = Vector3(m_alpha_x * w.x, m_alpha_y * w.y, w.z);
    wh.normalize();
    if (wh.z < 0.0f)
        wh = -wh;

    Frame frame(wh, Vector3::ZERO);
    Vector3 axis_x = frame.x_axis;
    Vector3 axis_y = frame.y_axis;

    float sample_x, sample_y;
    MathUtility::sampleFromUnitDisk(sample_x, sample_y);
    float h = 1.0f - std::sqrt(1.0f - MathUtility::sq(sample_x));
    float scale = (1 + wh.z) / 2.0f;
    float offset = 0.5f * h * (1.0f - wh.z);
    sample_y = sample_y * scale + offset;
    float pz = std::sqrt(1.0f - MathUtility::sq(sample_x) - MathUtility::sq(sample_y));

    Vector3 sampled_local_wm(sample_x, sample_y, pz);
    Vector3 sampled_wm = frame.pointToWorld(sampled_local_wm);
    sampled_wm.x *= m_alpha_x;
    sampled_wm.y *= m_alpha_y;
    sampled_wm.z = MathUtility::clamp(sampled_wm.z, 0.0f, 1.0f);

    return sampled_wm;
}

float Microfacet::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    Vector3 wm = wo + wi;
    if (wm.lenthSqr() == 0.0f)
        return 0.0f;

    wm.faceForward(Vector3(0,0,1));
    float absDot = std::abs(wo * wm);
    float r = d(wo, wm)  / (4.0f * absDot);

    return r;
}

// Color Microfacet::sample(const Vector3 &wo, Vector3 &wi, float &pdf) const
// {
//     return Color::COLOR_BLACK;
// }
