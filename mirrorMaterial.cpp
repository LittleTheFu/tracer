#include "mirrorMaterial.h"
#include "mirror.h"

MirrorMaterial::MirrorMaterial()
{
    m_pBrdf = new Mirror();
}