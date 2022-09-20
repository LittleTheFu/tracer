#ifndef _PLANE_H_
#define _PLANE_H_

#include "vector.h"

class Plane
{
public:
    Plane(const Vector3 &center, const Vector3 &normal);

    Vector3 center;
    Vector3 normal;
};

#endif