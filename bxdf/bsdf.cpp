#include "bsdf.h"
#include "mathUtility.h"

Bsdf::Bsdf(const Vector3 &ns_world)
{
    ns_world_ = ns_world;
}

void Bsdf::addBxdf(std::shared_ptr<Bxdf> bxdf)
{
    bxdfs_.push_back(bxdf);
}

Color Bsdf::f(const Vector3 &wo, const Vector3 &wi, BxdfType flags) const
{
    Color f = Color::COLOR_BLACK;

    for (const auto &bxdf : bxdfs_)
    {
        if (bxdf->isType(flags))
        {
            f += bxdf->f(wo, wi);
        }
    }

    return f;
}

float Bsdf::pdf(const Vector3 &wo, const Vector3 &wi, BxdfType flags) const
{
    float pdf = 0;

    for (const auto &bxdf : bxdfs_)
    {
        if (bxdf->isType(flags))
        {
            pdf += bxdf->pdf(wo, wi);
        }
    }

    return pdf;
}

Color Bsdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, BxdfType flags) const
{
    std::vector<std::shared_ptr<Bxdf>> bxdfs;

    for (const auto &bxdf : bxdfs_)
    {
        if (bxdf->isType(flags))
        {
            bxdfs.push_back(bxdf);
        }
    }

    if (bxdfs.empty())
    {
        pdf = 0;
        return Color::COLOR_BLACK;
    }

    int index = MathUtility::sampleUniformly(bxdfs.size());

    Color f = bxdfs[index]->sample_f(wo, wi, pdf);
    pdf /= bxdfs.size();

    return f;
}
