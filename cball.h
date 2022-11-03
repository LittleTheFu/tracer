#ifndef _C_BALL_H_
#define _C_BALL_H_

#include "geometry.h"
#include "rmaterial.h"

class CBall : public Geometry
{
public:
    CBall(const Vector3 &rotate, const Vector3 &position, float r, Rmaterial *pMtrl);
    virtual bool hit(const Ray &ray, HitRecord &record) const;
    virtual Vector3 sampleFromPoint(const Vector3 &thatPoint, float &pdf) const;

    float r;
    Rmaterial *m_pMtrl;

private:
    virtual Vector3 dpdu(const Vector3 &point) const;
    virtual Vector3 dpdv(const Vector3 &point) const;

    Vector3 getLocalNormal(const Vector3 &point) const;

    float getPhi(const Vector3 &point) const;
    float getTheta(const Vector3 &point) const;
};

#endif