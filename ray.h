#ifndef _RAY_H_
#define _RAY_H_

#include "vector.h"
#include "transform.h"

class Ray
{
public:
    Ray(const Vector3 &origin, const Vector3 &dir);

    Vector3 origin;
    Vector3 dir;
    float t;

    Ray genNewRay(const Transform &transform) const;
    static float getT(const Ray &ray, const Vector3 &thatPoint);

    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);
};

#endif