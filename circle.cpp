#include "circle.h"

Circle::Circle(const Vector3 &center, const Vector3 &normal, float r)
{
    this->center = center;
    this->normal = normal;
    this->r = r;
}
