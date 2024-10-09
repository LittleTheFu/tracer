#ifndef _BOUND_BOX_H_
#define _BOUND_BOX_H_

#include "vector.h"
#include <ray.h>

class BoundBox
{
public:
    BoundBox();
    BoundBox(const Vector3 &p1, const Vector3 &p2);

    void set(const Vector3 &p1, const Vector3 &p2);
    
    bool isInBox(const Vector3 &point) const;
    bool hit(const Ray &ray, float &tMin, float &tMax) const;

public:
    Vector3 minPoint;
    Vector3 maxPoint;
};

#endif