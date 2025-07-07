#include "materialSilk.h"
#include "measuredBxdf.h"
#include "resourceDef.h"

MaterialSilk::MaterialSilk()
{
}

std::unique_ptr<Bsdf> MaterialSilk::createBsdf(const Interaction &interaction)
{
    //quick and dirty,maybe in the future we will create a manager
    static std::shared_ptr<MeasuredBxdf> measuredBxdf = std::make_shared<MeasuredBxdf>(ResourceDef::BRDF_SARI_SILK);

    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);
    bsdf->addBxdf(measuredBxdf);

    return bsdf;
};