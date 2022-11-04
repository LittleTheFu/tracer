#include "brdf.h"

const Vector3 Brdf::LOCAL_NORMAL = Vector3(0, 0, 1);

bool Brdf::canLitByDirectLight() const
{
    return true;
}