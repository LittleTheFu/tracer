#include "plane.h"
#include <cmath>
#include <limits>

Plane::Plane(const Vector3 &center, const Vector3 &normal, const float r)
{
    this->center = center;
    this->normal = normal;
    this->r = r;

    this->normal.normalize();

    // transform.translate(center.x, center.y, center.z);
}

bool Plane::isLocalIn(const Vector3 &p) const
{
    float distSqr = (getLocalCenter() - p).lenthSqr();

    return distSqr <= (r * r);
}

bool Plane::isIn(const Vector3 &p) const
{
    float distSqr = (center - p).lenthSqr();

    return distSqr <= (r * r);
}

bool Plane::isInSamePlane(const Vector3 &p) const
{
    return false;

    Vector3 v = p - center;

    float r = v * normal;
    float rr = abs(r);

    // float t = std::numeric_limits<float>::min();
    // return rr < 0.00000000001;
    return rr == 0;
}

void Plane::setMaterial(const Material &mtrl)
{
    this->mtrl = mtrl;
}

Vector3 Plane::getLocalNormal() const
{
    return Vector3(0, 0, 1);
}

Vector3 Plane::getLocalCenter() const
{
    return Vector3(0, 0, 0);
}
