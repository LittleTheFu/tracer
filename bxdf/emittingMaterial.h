#ifndef _EMITTING_MATERIAL_H_
#define _EMITTING_MATERIAL_H_

#include "materialPlus.h"

class EmittingMaterial : public MaterialPlus
{
public:
    EmittingMaterial() = default;
    virtual ~EmittingMaterial() = default;

public:
    virtual bool isEmitting() const override;
    virtual Color getEmittedRadiance() const override;

private:

};

#endif