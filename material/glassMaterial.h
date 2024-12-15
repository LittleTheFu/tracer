#ifndef _GLASS_MATERIAL_H_
#define _GLASS_MATERIAL_H_

#include "material.h"
#include "glass.h"

class GlassMaterial : public Material
{
public:
    GlassMaterial();

    virtual Color get_f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta) override;

private:
    Glass *m_pGlassBrdf;
};

#endif