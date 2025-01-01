#ifndef _REFREACTOR_MATERIAL_H_
#define _REFREACTOR_MATERIAL_H_

#include "material.h"
#include "refreactorBsdf.h"

class RefreactorMaterial : public Material
{
public:
    RefreactorMaterial();

    virtual Color eval(float u,
                       float v,
                       const Vector3 &wo,
                       Vector3 &wi,
                       float &pdf,
                       bool &isDelta,
                       std::shared_ptr<Brdf> &brdf) override;

private:
    RefrectorBsdf *m_pRefreactorBsdf;
};

#endif