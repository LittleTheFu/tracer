#ifndef _MIRROR_MATERIAL_H_
#define _MIRROR_MATERIAL_H_

#include "material.h"
#include "mirror.h"
class MirrorMaterial : public Material
{
public:
    MirrorMaterial();

    virtual Color get_f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual Color eval(float u,
                       float v,
                       const Vector3 &wo,
                       Vector3 &wi,
                       float &pdf,
                       bool &isDelta,
                       std::shared_ptr<Brdf> &brdf) override;

private:
    Mirror *m_pMirrorBrdf;
};

#endif