#ifndef _MIX_MATERIAL_H_
#define _MIX_MATERIAL_H_

#include "material.h"
#include "glass.h"
#include "mirror.h"

class MixMaterial : public Material
{
public:
    MixMaterial();
    virtual bool isMirror() const override;
    virtual bool isDelta() const override;

    Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const;

private:
    Glass *m_pGlassBrdf;
    Mirror *m_pMirrorBrdf;

    float m_etaOutside;
    float m_etaInside;
};

#endif