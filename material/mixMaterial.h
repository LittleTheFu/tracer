#ifndef _MIX_MATERIAL_H_
#define _MIX_MATERIAL_H_

#include "material.h"
#include "glass.h"
#include "mirror.h"

//this class should be renamed to something like related to "glass"
class MixMaterial : public Material
{
public:
    MixMaterial();
    virtual bool isMirror() const override;
    virtual bool isDelta() const override;

    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const override;

private:
    Glass *m_pGlassBrdf;
    Mirror *m_pMirrorBrdf;

    float m_etaOutside;
    float m_etaInside;
};

#endif