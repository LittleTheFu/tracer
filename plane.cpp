#include "plane.h"
#include <cmath>
#include <limits>
#include "common.h"

Plane::Plane(const Vector3 &center, const Vector3 &normal, const float length)
{
    this->center = center;
    this->normal = normal;
    this->length = length;

    this->normal.normalize();

    // transform.translate(center.x, center.y, center.z);
}

bool Plane::isLocalIn(const Vector3 &p) const
{
    const float absZ = std::abs(p.z);
    if (absZ > Common::FLOAT_SAMLL_NUMBER)
        return false;

    const float half_length = length / 2;

    const float absX = std::abs(p.x);
    if (absX > half_length)
        return false;

    const float absY = std::abs(p.y);
    if (absY > half_length)
        return false;

    return true;
    // float distSqr = (getLocalCenter() - p).lenthSqr();

    // return distSqr <= (length * length);
}

bool Plane::isIn(const Vector3 &p) const
{
    const Vector3 localP = transform.invTransformPoint(p);

    const float absZ = std::abs(localP.z);
    if (absZ > Common::FLOAT_SAMLL_NUMBER)
        return false;

    const float half_length = length / 2;

    const float absX = std::abs(localP.x);
    if (absX > half_length)
        return false;

    const float absY = std::abs(localP.y);
    if (absY > half_length)
        return false;

    return true;

    // float distSqr = (center - p).lenthSqr();

    // return distSqr <= (length * length);
}

bool Plane::isOnThePlane(const Vector3 &p) const
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
