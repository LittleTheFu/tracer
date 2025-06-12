#include "materialLambertian.h"
#include "lambertianReflection.h"

MaterialLambertian::MaterialLambertian()
{
    albedo_ = Color::COLOR_PINK;
};

MaterialLambertian::MaterialLambertian(const Color &albedo)
{
    albedo_ = albedo;
}
std::unique_ptr<Bsdf> MaterialLambertian::createBsdf(const Interaction &interaction)
{
    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);
    bsdf->addBxdf(std::make_shared<LambertianReflection>(albedo_));

    return bsdf;
};