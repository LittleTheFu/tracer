#include "glassMaterial.h"
#include "glass.h"

GlassMaterial::GlassMaterial()
{
    m_pBrdf = new Glass(1, 1.5);
}