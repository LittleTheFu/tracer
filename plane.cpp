#include "plane.h"

Plane::Plane(const Vector3 &center, const Vector3 &normal)
{
    this->center = center;
    this->normal = normal;
    
    this->normal.normalize();
}