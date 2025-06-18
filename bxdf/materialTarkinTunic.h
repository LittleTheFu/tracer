#ifndef _MATERIAL_TARKIN_TUNIC_H_
#define _MATERIAL_TARKIN_TUNIC_H_

#include "materialPlus.h"
#include "color.h"

class MaterialTarkinTunic : public Material
{
public:
    MaterialTarkinTunic();

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
};

#endif