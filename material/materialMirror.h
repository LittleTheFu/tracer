#ifndef _MATERIAL_MIRROR_H_
#define _MATERIAL_MIRROR_H_

#include "material.h"
#include "color.h"

class MaterialMirror : public Material
{
public:
    MaterialMirror();

    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) override;
    
private:
    Color albedo_;
};

#endif