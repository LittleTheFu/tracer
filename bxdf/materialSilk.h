#ifndef _MATERIAL_SILK_H_
#define _MATERIAL_SILK_H_

#include "materialPlus.h"
#include "color.h"

class MaterialSilk : public MaterialPlus
{
public:
    MaterialSilk();

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
};

#endif