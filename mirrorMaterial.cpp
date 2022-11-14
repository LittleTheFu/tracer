#include "mirrorMaterial.h"
#include "mirror.h"

MirrorMaterial::MirrorMaterial()
{
    m_pMirrorBrdf = new Mirror();
}

bool MirrorMaterial::isMirror() const
{
    return true;
}
