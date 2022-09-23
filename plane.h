#ifndef _PLANE_H_
#define _PLANE_H_

#include "vector.h"

class Plane
{
public:
    Plane(const Vector3 &center, const Vector3 &normal, const float r = 30);

    bool isIn(const Vector3 &p) const;
    bool isInSamePlane(const Vector3 &p) const;

    Vector3 center;
    Vector3 normal;
    float r;
};

#endif