#ifndef _MATERIAL_PBR_H_
#define _MATERIAL_PBR_H_

#include "material.h"

class MaterialPBR : public Material
{
public:
    MaterialPBR(const Color &albedo, float roughness, float metallic);

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;

private:
    Color albedo_;
    float roughness_;
    float metallic_;
};

#endif