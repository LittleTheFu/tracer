#ifndef _C_PLANE_H_
#define _C_PLANE_H_

#include "geometry.h"
#include "material.h"

class Plane : public Geometry
{
public:
    Plane(const Vector3 &rotate, const Vector3 &position, float length, Material *pMtrl);
    virtual bool hit(const Ray &ray, HitRecord &record) const;

    float length;
    Material *m_pMtrl;

private:
    virtual Vector3 dpdu(const Vector3 &point) const;
    virtual Vector3 dpdv(const Vector3 &point) const;

    Vector3 getLocalNormal() const;
    bool isLocalIn(const Vector3 &p) const;
};

#endif