#ifndef _MATERIAL_GLASS_H_
#define _MATERIAL_GLASS_H_

#include "material.h"

class MaterialGlass : public Material
{
public:
    MaterialGlass();

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
};

#endif