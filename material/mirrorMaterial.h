#ifndef _MIRROR_MATERIAL_H_
#define _MIRROR_MATERIAL_H_

#include "material.h"
#include "mirror.h"
class MirrorMaterial : public Material
{
public:
    MirrorMaterial();
    virtual bool isMirror() const override;

    virtual bool isDelta() const override;
    Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const;

private:
    Mirror *m_pMirrorBrdf;
};

#endif