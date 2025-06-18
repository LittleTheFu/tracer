#ifndef _MATERIAL_LAMBERTIAN_H_
#define _MATERIAL_LAMBERTIAN_H_

#include "materialPlus.h"
#include "color.h"

class MaterialLambertian : public Material
{
public:
    MaterialLambertian(const Color &albedo);
    MaterialLambertian(const std::shared_ptr<ImageTexture> albedoTexture);

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
    
private:
    Color albedo_;
};

#endif