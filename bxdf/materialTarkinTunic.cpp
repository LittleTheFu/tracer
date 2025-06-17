#include "materialTarkinTunic.h"
#include "measuredBxdf.h"
#include "resourceDef.h"

MaterialTarkinTunic::MaterialTarkinTunic()
{
}

std::unique_ptr<Bsdf> MaterialTarkinTunic::createBsdf(const Interaction &interaction)
{
    //quick and dirty,maybe in the future we will create a manager
    static std::shared_ptr<MeasuredBxdf> measuredBxdf = std::make_shared<MeasuredBxdf>(ResourceDef::BRDF_TARKIN_TUNIC);

    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);
    bsdf->addBxdf(measuredBxdf);

    return bsdf;
};