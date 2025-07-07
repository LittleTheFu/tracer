#include "materialRough.h"
#include "lambertianBxdf.h"
#include <cassert>
#include <microfacetSpecularBxdf.h>

MaterialRough::MaterialRough()
{
}

std::unique_ptr<Bsdf> MaterialRough::createBsdf(const Interaction &interaction)
{
    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);

    bsdf->addBxdf(std::make_shared<MicrofacetSpecularBxdf>(0.2f, Color::COLOR_WHITE));

    return bsdf;
};