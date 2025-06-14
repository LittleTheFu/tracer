#include "materialPVC.h"
#include "measuredBxdf.h"
#include "resourceDef.h"

MaterialPVC::MaterialPVC()
{
}

std::unique_ptr<Bsdf> MaterialPVC::createBsdf(const Interaction &interaction)
{
    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);
    bsdf->addBxdf(std::make_shared<MeasuredBxdf>(ResourceDef::BRDF_GREEN_PVC));

    return bsdf;
};