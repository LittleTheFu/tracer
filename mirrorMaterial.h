#ifndef _MIRROR_MATERIAL_H_
#define _MIRROR_MATERIAL_H_

#include "material.h"
#include "mirror.h"
class MirrorMaterial : public Material
{
public:
    MirrorMaterial();
    bool isMirror() const;

    Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const;

private:
    Mirror *m_pMirrorBrdf;
};

#endif