#include "measuredBrdf.h"
#include "mathUtility.h"
#include "resourceDef.h"
#include <cassert>
#include "mathConstantDef.h"
#include "converter.h"

MeasuredBrdf::MeasuredBrdf(const std::string &file)
{
    m_pBrdf = std::make_shared<powitacq_rgb::BRDF>(file);
    assert(m_pBrdf);
}

Color MeasuredBrdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    float rnd_0 = MathUtility::genRandomDecimal();
    float rnd_1 = MathUtility::genRandomDecimal();
    powitacq_rgb::Vector2f wrapper_rnd(rnd_0, rnd_1);

    //take care of the order of wo and wi here
    powitacq_rgb::Vector3f wrapper_wo = ThirdInterfaceConverter::toPowitVec(wo);
    powitacq_rgb::Vector3f wrapper_wi;
    powitacq_rgb::Vector3f wrapper_color;

    wrapper_color = m_pBrdf->sample(wrapper_rnd, wrapper_wo, &wrapper_wi, &pdf);

    wi = ThirdInterfaceConverter::toVec(wrapper_wi);
    Color color = ThirdInterfaceConverter::toColor(wrapper_color);

    return color;
}

float MeasuredBrdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    //take care of the order of wo and wi here
    powitacq_rgb::Vector3f wrapper_wi = ThirdInterfaceConverter::toPowitVec(wo);
    powitacq_rgb::Vector3f wrapper_wo = ThirdInterfaceConverter::toPowitVec(wi);

    float pdf = m_pBrdf->pdf(wrapper_wi, wrapper_wo);

    return pdf;
}

Color MeasuredBrdf::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    powitacq_rgb::Vector3f wrapper_wo = ThirdInterfaceConverter::toPowitVec(wo);   
    powitacq_rgb::Vector3f wrapper_wi = ThirdInterfaceConverter::toPowitVec(wi);

    //Warnning: care about the order of wo and wi here
    powitacq_rgb::Vector3f f = m_pBrdf->eval(wrapper_wo, wrapper_wi);
    Color ff(f.x(), f.y(), f.z());

    return ff;
}

std::shared_ptr<Brdf> MeasuredBrdf::clone() const
{
    return std::make_shared<MeasuredBrdf>(*this);
}
