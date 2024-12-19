#ifndef _CONDUCTOR_MATERIAL_H_
#define _CONDUCTOR_MATERIAL_H_

#include "material.h"
#include "conductorBrdf.h"

class ConductorMaterial : public Material
{
public:
    ConductorMaterial();

    virtual Color eval(float u,
                       float v,
                       const Vector3 &wo,
                       Vector3 &wi,
                       float &pdf,
                       bool &isDelta,
                       std::shared_ptr<Brdf> &brdf) override;

private:
    std::shared_ptr<ConductorBrdf> m_pConductorBrdf;
};

#endif