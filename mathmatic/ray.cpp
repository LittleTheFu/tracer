#include "ray.h"
#include <limits>
#include <cmath>
#include "common.h"
#include "frame.h"

Ray::Ray(const Vector3 &origin, const Vector3 &dir)
{
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
    const Vector3 o = frame.toLocal(origin);
    const Vector3 d = frame.toLocal(dir);

    return Ray(o, d);
}

float Ray::getT(const Ray &ray, const Vector3 &thatPoint)
{
    Vector3 d = thatPoint - ray.origin;
    if (ray.dir.x > ray.dir.y)
    {
        if (ray.dir.x > ray.dir.z)
        {
            return d.x / ray.dir.x;
        }
        else
        {
            return d.z / ray.dir.z;
        }
    }
    else
    {
        if (ray.dir.y > ray.dir.z)
        {
            return d.y / ray.dir.y;
        }
        else
        {
            return d.z / ray.dir.z;
        }
    }

    return 0;
}

std::ostream &operator<<(std::ostream &os, const Ray &ray)
{
    os << "ray --- origin : ( " << ray.origin << " ) , dir : ( " << ray.dir << " ) ";

    return os;
}
