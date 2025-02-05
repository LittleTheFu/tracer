#ifndef _DIELECTRIC_MATERIAL_H_
#define _DIELECTRIC_MATERIAL_H_

#include "material.h"
#include "refreactorBsdf.h"
#include "mirror.h"
#include "microfacet.h"

// this class should be renamed to something like related to "glass"
class DielectricMaterial : public Material
{
public:
    DielectricMaterial();

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

    Color eval_rough(float u,
                      float v,
                      const Vector3 &wo,
                      Vector3 &wi,
                      float &pdf,
                      bool &isDelta,
                      std::shared_ptr<Brdf> &brdf);

private:
    RefrectorBsdf *m_pGlassBrdf;
    Mirror *m_pMirrorBrdf;
    Brdf *m_pCurrentBrdf; // bad here,to be fixed later...

    float m_etaOutside;
    float m_etaInside;

    bool m_isSmooth;

    Microfacet m_microfacet;

};

#endif