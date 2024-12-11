#ifndef _GLASS_MATERIAL_H_
#define _GLASS_MATERIAL_H_

#include "material.h"
#include "glass.h"

class GlassMaterial : public Material
{
public:
    GlassMaterial();

    virtual bool isDelta() const override;
    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const override;

private:
    Glass *m_pGlassBrdf;
};

#endif