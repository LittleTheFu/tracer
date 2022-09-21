#ifndef _RAY_H_
#define _RAY_H_

#include "vector.h"
#include "ball.h"
#include "plane.h"

class Ray
{
public:
    Ray(const Vector3 &origin, const Vector3 &dir);

    Vector3 origin;
    Vector3 dir;
    float t;

    bool hit(const Ball &ball, float &t) const;
    bool hit(const Plane &plane, float &t) const;
};

#endif