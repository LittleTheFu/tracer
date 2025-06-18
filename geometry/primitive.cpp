#include "primitive.h"

bool Primitive::isEmitting() const
{
    if(getMaterial() == nullptr)
        return false;
        
    return getMaterial()->isEmitting();
}