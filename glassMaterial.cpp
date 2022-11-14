#include "glassMaterial.h"
#include "glass.h"

GlassMaterial::GlassMaterial()
{
    m_pGlassBrdf = new Glass(1, 1.5);
}

bool GlassMaterial::isMirror() const
{
    return true;
}