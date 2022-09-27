#ifndef _RAY_H_
#define _RAY_H_

#include "vector.h"
#include "ball.h"
#include "plane.h"
#include "transform.h"

class Ray
{
public:
    Ray(const Vector3 &origin, const Vector3 &dir);

    Vector3 origin;
    Vector3 dir;
    float t;

    bool hit(const Ball &ball, float &t, Vector3 &point) const;
    bool hit(const Plane &plane, float &t, Vector3 &point) const;

    bool localHit(const Ball &ball, float &t, Vector3 &point, Vector3 &normal, Vector3 &randomReflectVector) const;
    bool localHit(const Plane &plane, float &t, Vector3 &point, Vector3 &normal, Vector3 &randomReflectVector) const;
    // bool localHit(const Plane &plane, float &t, Vector3 &point) const;

    Ray genNewRay(const Transform &transform) const;

    float getDistranceT(const Vector3 &that) const;

    static float getT(const Ray &ray, const Vector3& thatPoint);
};

#endif