#include "materialGlass.h"
#include "dielectricBxdf.h"
#include "mediumBoundary.h"
#include "medium.h"


MaterialGlass::MaterialGlass()
{
}

std::unique_ptr<Bsdf> MaterialGlass::createBsdf(const Interaction &interaction)
{
    //hotfix,quick and dirty
    float etaI = interaction.mediumBoundary->mediumOutside_->eta_;
    float etaT = interaction.mediumBoundary->mediumInside_->eta_;

    bool isSameDir = interaction.incoming.isSameDir(interaction.normal_shading);
    if(isSameDir)
    {
        std::swap(etaI, etaT);
    }


    std::shared_ptr<DielectricBxdf> dielectricBxdf = std::make_shared<DielectricBxdf>(etaI, etaT);

    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);
    bsdf->addBxdf(dielectricBxdf);

    return bsdf;
};