#include "materialTRough.h"
#include <cassert>
#include <microfacetTransmissionBxdf.h>
#include "mediumBoundary.h"
#include "medium.h"

MaterialTRough::MaterialTRough()
{
}

std::unique_ptr<Bsdf> MaterialTRough::createBsdf(const Interaction &interaction)
{
    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);

    float etaI = interaction.mediumBoundary->mediumOutside_->eta_;
    float etaT = interaction.mediumBoundary->mediumInside_->eta_;

    bool isSameDir = interaction.incoming.isSameDir(interaction.normal_shading);
    if (isSameDir)
    {
        std::swap(etaI, etaT);
    }

    bsdf->addBxdf(std::make_shared<MicrofacetTransmissionBxdf>(0.4f, etaI, etaT));

    return bsdf;
};