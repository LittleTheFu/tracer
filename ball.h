#ifndef _BALL_H_
#define _BALL_H_

#include "vector.h"

class Ball
{
public:
    Ball(const Vector3 &center, float r);
    float r;

    Vector3 getCenter() const;
    Vector3 getNormal(const Vector3 &point) const;

private:
    Vector3 center;
};

#endif