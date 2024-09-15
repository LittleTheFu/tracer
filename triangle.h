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

    virtual bool hit(const Ray &ray, HitRecord &record, Light *pLight) const;

    Vector3 getLocalNormal(bool reverse) const;
    bool isAllFacePositive(const Vector3 &a, const Vector3 &b, const Vector3 &c) const;

private:
    void getCrossResult(const Vector3 &p,
                        Vector3 &apCrossAb,
                        Vector3 &apCrossBc,
                        Vector3 &apCrossCa) const;

private:
    virtual Vector3 dpdu(const Vector3 &point) const;
    virtual Vector3 dpdv(const Vector3 &point) const;

    virtual float u(const Vector3 &point) const;
    virtual float v(const Vector3 &point) const;

    void getWeight(const Vector3 &ap_ab,
                   const Vector3 &ap_bc,
                   const Vector3 &ap_ca,
                   float &weightA,
                   float &weightB,
                   float &weightC) const;

private:
    TriAngleVertex m_a;
    TriAngleVertex m_b;
    TriAngleVertex m_c;

    float m_doulbe_area;
};

#endif