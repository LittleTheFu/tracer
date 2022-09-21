#include "plane.h"

Plane::Plane(const Vector3 &center, const Vector3 &normal, const float r)
{
    this->center = center;
    this->normal = normal;
    this->r = r;

    this->normal.normalize();
}

bool Plane::isIn(const Vector3 &p) const
{
    float distSqr = (center - p).lenthSqr();

    return distSqr <= (r * r);
}
