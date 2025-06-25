#include "bsdf.h"
#include "mathUtility.h"
#include <cassert>

Bsdf::Bsdf(const Vector3 &ns_world)
{
    nsWorld_ = ns_world;

    MathUtility::buildBTN(nsWorld_, tLocal_, bLocal_, nLocal_);
    tbnFrame_.setTBN(tLocal_, bLocal_, nLocal_);
}

void Bsdf::addBxdf(std::shared_ptr<Bxdf> bxdf)
{
    bxdfs_.push_back(bxdf);
}

Color Bsdf::f(const Vector3 &wo, const Vector3 &wi, BxdfType flags) const
{
    Color f = Color::COLOR_BLACK;

    Vector3 wo_local = tbnFrame_.vectorToLocal(wo);
    Vector3 wi_local = tbnFrame_.vectorToLocal(wi);

    for (const auto &bxdf : bxdfs_)
    {
        if (bxdf->isType(flags))
        {
            f += bxdf->f(wo_local, wi_local);
        }
    }

    return f;
}

float Bsdf::pdf(const Vector3 &wo, const Vector3 &wi, BxdfType flags) const
{
    float pdf = 0;

    Vector3 wo_local = tbnFrame_.vectorToLocal(wo);
    Vector3 wi_local = tbnFrame_.vectorToLocal(wi);

    for (const auto &bxdf : bxdfs_)
    {
        if (bxdf->isType(flags))
        {
            pdf += bxdf->pdf(wo_local, wi_local);
        }
    }

    return pdf;
}

Color Bsdf::sample_f(const Vector3 &wo,
                     Vector3 &wi,
                     float &pdf,
                     BxdfType &sampledType,
                     const Interaction &interaction,
                     BxdfType flags) const
{
    std::vector<std::shared_ptr<Bxdf>> bxdfs;

    Frame localFrame(tbnFrame_);
    if(interaction.hasNormalMap())
    {
        Vector3 mapN = interaction.getNormalFromNormalMap(interaction.u, interaction.v);
        Vector3 newNormal = tbnFrame_.vectorToWorld(mapN);

        Vector3 newT, newB, newN;
        MathUtility::buildBTN(newNormal, newB, newT, newN);
        localFrame.setTBN(newT, newB, newN);
    }

    Vector3 wo_local = localFrame.vectorToLocal(wo);

    for (const auto &bxdf : bxdfs_)
    {
        if (bxdf->isType(flags))
        // if(true)
        {
            bxdfs.push_back(bxdf);
        }
    }

    if (bxdfs.empty())
    {
        pdf = 0;
        return Color::COLOR_BLACK;
    }

    //hack,bug,to be fixed later
    int index = MathUtility::sampleUniformly(bxdfs.size());
    if (index >= bxdfs.size())
    {
        //for debug
        assert(0);
        index = bxdfs.size() - 1;
    }

    Vector3 wi_local;
    Color f = bxdfs[index]->sample_f(wo_local, wi_local, pdf, interaction);
    sampledType = bxdfs[index]->getType();
    wi = localFrame.vectorToWorld(wi_local);
    
    pdf /= bxdfs.size();

    if (hasFlag(sampledType, BxdfType::SPECULAR))
    {
        // pdf = 1;
    }

    return f;
}

bool Bsdf::hasSpecular() const
{
    for (const auto &bxdf : bxdfs_)
    {
        if (hasFlag(bxdf->getType(), BxdfType::SPECULAR))
        {
            return true;
        }
    }

    return false;
}
