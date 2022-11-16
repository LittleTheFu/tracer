#ifndef _C_BALL_H_
#define _C_BALL_H_

#include "geometry.h"
#include "material.h"

class Ball : public Geometry
{
public:
    Ball();
    Ball(const Vector3 &rotate, const Vector3 &position, float r, Material *pMtrl);

    virtual bool hit(const Ray &ray, HitRecord &record) const;
    virtual Vector3 sampleFromPoint(const Vector3 &thatPoint, float &pdf) const;
    Vector3 getLocalDirection(float u, float v) const;

    float r;
    
private:
    virtual Vector3 dpdu(const Vector3 &point) const;
    virtual Vector3 dpdv(const Vector3 &point) const;

    virtual float u(const Vector3 &point) const;
    virtual float v(const Vector3 &point) const;

    Vector3 getLocalNormal(const Vector3 &point) const;

    float getPhi(const Vector3 &point) const;
    float getTheta(const Vector3 &point) const;
};

#endif