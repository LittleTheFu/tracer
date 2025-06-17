#include "materialLambertian.h"
#include "lambertianReflection.h"
#include <cassert>

MaterialLambertian::MaterialLambertian(const Color &albedo)
{
    albedo_ = albedo;
}
MaterialLambertian::MaterialLambertian(const std::shared_ptr<ImageTexture> albedoTexture)
{
    assert(albedoTexture);
    albedoTexture_ = albedoTexture;

    albedo_ = Color::COLOR_PINK;
}

std::unique_ptr<Bsdf> MaterialLambertian::createBsdf(const Interaction &interaction)
{
    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);

    Color color = albedo_;
    if(albedoTexture_)
    {
        color = albedoTexture_->getColor(interaction.u, interaction.v);
    }
    bsdf->addBxdf(std::make_shared<LambertianReflection>(color));

    return bsdf;
};