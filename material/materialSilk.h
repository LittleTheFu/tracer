#ifndef _MATERIAL_SILK_H_
#define _MATERIAL_SILK_H_

#include "material.h"
#include "color.h"

class MaterialSilk : public Material
{
public:
    MaterialSilk();

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
};

#endif