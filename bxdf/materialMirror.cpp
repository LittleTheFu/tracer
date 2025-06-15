#include "materialMirror.h"
#include "lambertianReflection.h"
#include "specularBxdf.h"

MaterialMirror::MaterialMirror()
{
};


std::unique_ptr<Bsdf> MaterialMirror::createBsdf(const Interaction &interaction)
{
    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);
    bsdf->addBxdf(std::make_shared<SpecularBxdf>());

    return bsdf;
};