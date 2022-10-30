#ifndef _C_BALL_H_
#define _C_BALL_H_

#include "geometry.h"

class CBall : public Geometry
{
public:
    CBall(const Vector3 &rotate, const Vector3 &position, float r);
    virtual bool hit(const Ray &ray, HitRecord &record) const;

    float r;

private:
    virtual Vector3 dpdu(const Vector3 &point) const;
    virtual Vector3 dpdv(const Vector3 &point) const;

    Vector3 getLocalNormal(const Vector3 &point) const;

    float getPhi(const Vector3 &point) const;
    float getTheta(const Vector3 &point) const;
};

#endif