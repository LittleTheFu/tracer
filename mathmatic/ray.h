#ifndef _RAY_H_
#define _RAY_H_

#include "frame.h"
#include "media.h"
#include "transform.h"
#include "vector.h"

class Ray
{
public:
    Ray();
    Ray(const Vector3 &origin, const Vector3 &dir);

    Vector3 origin;
    Vector3 dir;
    float t;
    Media media;

    Ray genNewRay(const Transform &transform) const;
    Ray genNewRay(const Frame &frame) const;

    Vector3 getPosition(float t) const;

    static float getT(const Ray &ray, const Vector3 &thatPoint);

    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);
};

#endif