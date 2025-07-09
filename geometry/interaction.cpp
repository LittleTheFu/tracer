#include "interaction.h"
#include "primitive.h"


bool Interaction::hasNormalMap() const
{
    if (primitive == nullptr)
        return false;

    if(primitive->getMaterial() == nullptr)
        return false;

    if(primitive->getMaterial()->getNormalTexture() == nullptr)
        return false;
        
    return true;
}

Vector3 Interaction::getNormalFromNormalMap(float u, float v) const
{
    Vector3 normal = primitive->getMaterial()->getNormalTexture()->getNormal(u, v);

    return normal;
}

bool Interaction::isHitFromOutside() const
{
    return !incoming.isSameDir(normal_geometry);
}
