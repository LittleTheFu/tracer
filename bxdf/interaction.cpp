#include "interaction.h"
#include "primitive.h"


bool Interaction::hasNormalMap() const
{
    if (primitive == nullptr)
        return false;

    if(primitive->getMaterial() == nullptr)
        return false;

    if(primitive->getMaterial()->getNormalTexture() != nullptr)
        return false;
        
    return true;
}

Vector3 Interaction::getNormalFromNormalMap(float u, float v) const
{
    Vector3 normal = primitive->getMaterial()->getNormalTexture()->getNormal(u, v);

    normal = normal * 2.0f - Vector3(1, 1, 1);
    normal.normalize();
    
    return normal;
}
