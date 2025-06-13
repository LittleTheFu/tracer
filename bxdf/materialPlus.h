#ifndef _MATERIAL_PLUS_H_
#define _MATERIAL_PLUS_H_

#include "bsdf.h"
#include "imageTexture.h"
#include "normalTexture.h"
#include "interaction.h"
#include <memory>
#include "color.h"


class MaterialPlus
{
public:
    MaterialPlus() = default;
    virtual ~MaterialPlus() = default;

public:
    virtual std::unique_ptr<Bsdf> createBsdf(const Interaction& interaction);

    virtual bool isEmitting() const;
    virtual Color getEmittedRadiance() const;

protected:
    std::shared_ptr<ImageTexture> albedo_;
    std::shared_ptr<NormalTexture> normal_;
};

#endif