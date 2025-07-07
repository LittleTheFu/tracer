#include "materialPBR.h"
#include <algorithm>
#include <lambertianBxdf.h>
#include <microfacetSpecularBxdf.h>
#include <dielectricBxdf.h>

MaterialPBR::MaterialPBR(const Color &albedo, float roughness, float metallic)
    : albedo_(albedo),
      roughness_(roughness),
      metallic_(metallic)
{
    roughness_ = std::clamp(roughness_, 0.0f, 1.0f);
    metallic_ = std::clamp(metallic_, 0.0f, 1.0f);
}

std::unique_ptr<Bsdf> MaterialPBR::createBsdf(const Interaction &interaction)
{
    std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);

    Color currentAlbedo = albedo_;
    float currentRoughness = roughness_;
    float currentMetallic = metallic_;

    Color dielectricF0 = Color(0.04f, 0.04f, 0.04f);
    Color specularF0 = Color::lerp(dielectricF0, currentAlbedo, currentMetallic);

    Color diffuseColor = currentAlbedo * (Color(1.0f) - specularF0);
    diffuseColor.clamp();

    bsdf->addBxdf(std::make_unique<LambertianBxdf>(diffuseColor));
    bsdf->addBxdf(std::make_unique<MicrofacetSpecularBxdf>(currentRoughness, specularF0));
    // bsdf->addBxdf(std::make_unique<DielectricBxdf>());

    return bsdf;
}
