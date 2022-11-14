#ifndef _GLASS_MATERIAL_H_
#define _GLASS_MATERIAL_H_

#include "material.h"
#include "glass.h"

class GlassMaterial : public Material
{
public:
    GlassMaterial();
    bool isMirror() const;

private:
    Glass *m_pGlassBrdf;
};

#endif