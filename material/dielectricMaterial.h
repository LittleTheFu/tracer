#ifndef _MIX_MATERIAL_H_
#define _MIX_MATERIAL_H_

#include "material.h"
#include "glass.h"
#include "mirror.h"

//this class should be renamed to something like related to "glass"
class DielectricMaterial : public Material
{
public:
    DielectricMaterial();

    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta) const override;

private:
    Glass *m_pGlassBrdf;
    Mirror *m_pMirrorBrdf;

    float m_etaOutside;
    float m_etaInside;
};

#endif