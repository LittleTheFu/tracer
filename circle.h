#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "vector.h"
#include "material.h"

class Circle
{
public:
    Circle(const Vector3 &center, const Vector3 &normal, float r);

    // //u~phi, v~theta
    // Vector3 dpdu(const Vector3 &p);
    // Vector3 dpdv(const Vector3 &p);
private:
    // float getPhi(const Vector3 &p);
    // float getTheta(const Vector3 &p);

    Vector3 center;
    Vector3 normal;
    float r;
};

#endif