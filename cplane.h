#ifndef _C_PLANE_H_
#define _C_PLANE_H_

#include "geometry.h"

class CPlane : public Geometry
{
public:
    CPlane(const Vector3 &rotate, const Vector3 &position, float length);
    virtual bool hit(const Ray &ray, HitRecord &record) const;

    float length;

private:
    virtual Vector3 dpdu(const Vector3 &point) const;
    virtual Vector3 dpdv(const Vector3 &point) const;

    Vector3 getLocalNormal() const;
    bool isLocalIn(const Vector3 &p) const;


};

#endif