#ifndef _TRI_ANGLE_H_
#define _TRI_ANGLE_H_

#include "geometry.h"

class TriAngleVertex
{
public:
    TriAngleVertex();
    TriAngleVertex(float x, float y, float u, float v);

    float x;
    float y;
    float u;
    float v;
};

class TriAngle : public Geometry
{
public:
    TriAngle(const TriAngleVertex &a,
             const TriAngleVertex &b,
             const TriAngleVertex &c,
             const Vector3 &rotate,
             const Vector3 &position,
             Material *pMtrl);

    virtual bool hit(const Ray &ray, HitRecord &record) const;

    Vector3 getLocalNormal(bool reverse) const;
    bool isLocalIn(const Vector3 &p) const;

private:
    virtual Vector3 dpdu(const Vector3 &point) const;
    virtual Vector3 dpdv(const Vector3 &point) const;

    virtual float u(const Vector3 &point) const;
    virtual float v(const Vector3 &point) const;

private:
    TriAngleVertex m_a;
    TriAngleVertex m_b;
    TriAngleVertex m_c;
};

#endif