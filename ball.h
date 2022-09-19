#ifndef _BALL_H_
#define _BALL_H_

#include "vector.h"

class Ball
{
public:
    Ball(const Vector3 &center, float r);
    float r;

    Vector3 getCenter() const;

private:
    Vector3 center;
};

#endif