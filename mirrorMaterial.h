#ifndef _MIRROR_MATERIAL_H_
#define _MIRROR_MATERIAL_H_

#include "material.h"
#include "mirror.h"
class MirrorMaterial : public Material
{
public:
    MirrorMaterial();
    bool isMirror() const;

private:
    Mirror *m_pMirrorBrdf;
};

#endif