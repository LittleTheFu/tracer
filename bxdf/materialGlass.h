#ifndef _MATERIAL_GLASS_H_
#define _MATERIAL_GLASS_H_

#include "materialPlus.h"

class MaterialGlass : public MaterialPlus
{
public:
    MaterialGlass();

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
};

#endif