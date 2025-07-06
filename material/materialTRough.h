#ifndef _MATERIAL_T_ROUGH_H_
#define _MATERIAL_T_ROUGH_H_

#include "material.h"
#include "color.h"

class MaterialTRough : public Material
{
public:
    MaterialTRough();
    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
};

#endif