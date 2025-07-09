#ifndef _MATERIAL_PBR_H_
#define _MATERIAL_PBR_H_

#include "material.h"

//at this moment it's not a pbr material,but I will change it later(maybe)
class MaterialPBR : public Material
{
public:
    MaterialPBR(const Color &albedo, float roughness, float metallic, std::unique_ptr<Texture> albedoTexture);

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;

private:
    Color albedo_;
    float roughness_;
    float metallic_;

    std::unique_ptr<Texture> albedoTexture_;
};

#endif