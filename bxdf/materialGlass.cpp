#include "materialGlass.h"
#include "dielectricBxdf.h"

MaterialGlass::MaterialGlass()
{
}

std::unique_ptr<Bsdf> MaterialGlass::createBsdf(const Interaction &interaction)
{
    float etaI = 1.0f;
    float etaT = 1.5f;

    bool isSameDir = interaction.incoming.isSameDir(interaction.normal_shading);
    if(isSameDir)
        std::swap(etaI, etaT);

    std::shared_ptr<DielectricBxdf> dielectricBxdf = std::make_shared<DielectricBxdf>(etaI, etaT);

    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);
    bsdf->addBxdf(dielectricBxdf);

    return bsdf;
};