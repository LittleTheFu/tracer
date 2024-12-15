#include "ray.h"
#include <limits>
#include <cmath>
#include "common.h"
#include "frame.h"
#include "mathUtility.h"

Ray::Ray()
{
    origin = Vector3::ZERO;
    dir = Vector3::ZERO;
}

Ray::Ray(const Vector3 &origin, const Vector3 &dir)
{
    this->media.clear();
    
    this->origin = origin;
    this->dir = dir;
    this->dir.normalize();
}

Ray Ray::genNewRay(const Transform &transform) const
{
    const Vector3 o = transform.invTransformPoint(origin);
    const Vector3 d = transform.invTransformVector(dir);

    return Ray(o, d);
}

Ray Ray::genNewRay(const Frame &frame) const
{
    const Vector3 o = frame.pointToLocal(origin);
    const Vector3 d = frame.vectorToLocal(dir);

    return Ray(o, d);
}

Vector3 Ray::getPosition(float t) const
{
    return origin + dir * t;
}

float Ray::getT(const Ray &ray, const Vector3 &thatPoint)
{
    Vector3 d = thatPoint - ray.origin;
    int index = MathUtility::getMaxIndex(ray.dir.x, ray.dir.y, ray.dir.z);

    if (index == 0)
        return d.x / ray.dir.x;
    else if (index == 1)
        return d.y / ray.dir.y;
    else
        return d.z / ray.dir.z;
}

std::ostream &operator<<(std::ostream &os, const Ray &ray)
{
    os << "ray --- origin : ( " << ray.origin << " ) , dir : ( " << ray.dir << " ) ";

    return os;
}
