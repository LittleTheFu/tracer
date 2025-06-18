#ifndef _MATERIAL_ROUGH_H_
#define _MATERIAL_ROUGH_H_

#include "material.h"
#include "color.h"

class MaterialRough : public Material
{
public:
    MaterialRough();
    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
};

#endif