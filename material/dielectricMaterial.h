#ifndef _DIELECTRIC_MATERIAL_H_
#define _DIELECTRIC_MATERIAL_H_

#include "material.h"
#include "glass.h"
#include "mirror.h"

// this class should be renamed to something like related to "glass"
class DielectricMaterial : public Material
{
public:
    DielectricMaterial();

    virtual Color get_f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual Color eval(float u,
                       float v,
                       const Vector3 &wo,
                       Vector3 &wi,
                       float &pdf,
                       bool &isDelta,
                       std::shared_ptr<Brdf> &brdf) override;

private:
    Color eval_smooth(float u,
                      float v,
                      const Vector3 &wo,
                      Vector3 &wi,
                      float &pdf,
                      bool &isDelta,
                      std::shared_ptr<Brdf> &brdf);

private:
    Glass *m_pGlassBrdf;
    Mirror *m_pMirrorBrdf;
    Brdf *m_pCurrentBrdf; // bad here,to be fixed later...

    float m_etaOutside;
    float m_etaInside;
};

#endif