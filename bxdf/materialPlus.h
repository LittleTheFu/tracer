#ifndef _MATERIAL_PLUS_H_
#define _MATERIAL_PLUS_H_

#include "bsdf.h"
#include "imageTexture.h"
#include "normalTexture.h"
#include "interaction.h"
#include <memory>


class MaterialPlus
{
public:
    MaterialPlus() = default;
    virtual ~MaterialPlus() = default;

public:
    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction) = 0;

protected:
    std::shared_ptr<ImageTexture> albedo_;
    std::shared_ptr<NormalTexture> normal_;
};

#endif