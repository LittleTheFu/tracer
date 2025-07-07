#include "measuredBxdf.h"
#include <cassert>
#include <mathUtility.h>
#include "converter.h"

MeasuredBxdf::MeasuredBxdf(const std::string &file)
    : Bxdf(BxdfType::MEASURED)
{
    brdf_ = std::make_shared<powitacq_rgb::BRDF>(file);
    assert(brdf_);
}

Color MeasuredBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const

{
    float rnd_0 = MathUtility::genRandomDecimal();
    float rnd_1 = MathUtility::genRandomDecimal();
    powitacq_rgb::Vector2f wrapper_rnd(rnd_0, rnd_1);

    // take care of the order of wo and wi here
    powitacq_rgb::Vector3f wrapper_wo = ThirdInterfaceConverter::toPowitVec(wo);
    powitacq_rgb::Vector3f wrapper_wi;
    powitacq_rgb::Vector3f wrapper_color;

    wrapper_color = brdf_->sample(wrapper_rnd, wrapper_wo, &wrapper_wi, &pdf);

    wi = ThirdInterfaceConverter::toVec(wrapper_wi);
    Color color = ThirdInterfaceConverter::toColor(wrapper_color);
    color = color * pdf;
    float absDot = std::abs(wi.z);
    if (absDot == 0.0f)
        return Color::COLOR_BLACK;
    color = color / absDot;

    return color;
}

float MeasuredBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    // take care of the order of wo and wi here
    powitacq_rgb::Vector3f wrapper_wi = ThirdInterfaceConverter::toPowitVec(wo);
    powitacq_rgb::Vector3f wrapper_wo = ThirdInterfaceConverter::toPowitVec(wi);

    float pdf = brdf_->pdf(wrapper_wi, wrapper_wo);

    return pdf;
}

Color MeasuredBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    powitacq_rgb::Vector3f wrapper_wo = ThirdInterfaceConverter::toPowitVec(wo);
    powitacq_rgb::Vector3f wrapper_wi = ThirdInterfaceConverter::toPowitVec(wi);

    // Warnning: care about the order of wo and wi here
    powitacq_rgb::Vector3f f = brdf_->eval(wrapper_wo, wrapper_wi);
    // f *= wrapper_wi.z();

    float absDot = std::abs(wrapper_wi.z());
    if (absDot == 0.0f)
        return Color::COLOR_BLACK;

    Color ff(f.x() / absDot, f.y() / absDot, f.z() / absDot);

    return ff;
}