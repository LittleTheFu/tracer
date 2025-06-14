#ifndef _MATERIAL_PVC_H_
#define _MATERIAL_PVC_H_

#include "materialPlus.h"
#include "color.h"

class MaterialPVC : public MaterialPlus
{
public:
    MaterialPVC();

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
};

#endif