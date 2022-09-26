#ifndef _BALL_H_
#define _BALL_H_

#include "vector.h"
#include "material.h"
#include "transform.h"

class Ball
{
public:
    Ball();
    Ball(const Vector3 &center, float r);

    void setPos(float x, float y, float z);
    void setR(float r);

    bool isInTheBall(const Vector3 &point);
    void setMaterial(const Material &mtrl);

    float r;

    Vector3 getLocalCenter() const;
    Vector3 getLocalNormal(const Vector3 &point) const;

    Vector3 getCenter() const;
    Vector3 getNormal(const Vector3 &point) const;

    Material mtrl;

    Transform transform;

private:
    Vector3 center;
};

#endif