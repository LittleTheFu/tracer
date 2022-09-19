#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "vector.h"

class Circle
{
public:
    Circle(const Vector3 &center, const Vector3 &normal, float r);

private:
    Vector3 center;
    Vector3 normal;
    float r;
};

#endif