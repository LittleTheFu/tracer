#ifndef _PLANE_H_
#define _PLANE_H_

#include "vector.h"
#include "material.h"
#include "transform.h"

class Plane
{
public:
    Plane(const Vector3 &center, const Vector3 &normal, const float r = 30);

    bool isLocalIn(const Vector3 &p) const;

    bool isIn(const Vector3 &p) const;
    bool isInSamePlane(const Vector3 &p) const;

    void setMaterial(const Material &mtrl);

    Vector3 getLocalNormal() const;
    Vector3 getLocalCenter() const;

    Material mtrl;

    Vector3 center;
    Vector3 normal;
    float r;

    Transform transform;
};

#endif