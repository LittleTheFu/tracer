#include "ray.h"
#include <limits>

Ray::Ray(const Vector3 &origin, const Vector3 &dir)
{
    this->origin = origin;
    this->dir = dir;
    this->dir.normalize();
}

bool Ray::hit(const Ball &ball, float &t) const
{
    t = std::numeric_limits<float>::max();

    const float a = dir.lenthSqr();
    const float b = 2 * (dir * origin - dir * ball.getCenter());
    const float c = origin.lenthSqr() +
                    ball.getCenter().lenthSqr() -
                    2 * (origin * ball.getCenter()) -
                    ball.r * ball.r;

    const float delta = b * b - 4 * a * c;

    if (delta < 0.0f)
        return false;

    float t0 = (-b + delta) / (2 * a);
    float t1 = (b + delta) / (2 * a);
    float temp = 0;
    if(t0 > t1)
    {
        temp = t0;
        t0 = t1;
        t1 = temp;
    }

    bool hit = t0 > 0.0f;
    t = t0;

    if (!hit)
    {
        hit = t1 > 0.0f;
        t = t1;
    }

    return hit;
}

bool Ray::hit(const Plane &plane, float &t) const
{
    t = std::numeric_limits<float>::max();

    if (dir * plane.normal > 0)
    {
        return false;
    }

    const float n = (plane.center - origin) * plane.normal;
    const float d = dir * plane.normal;

    t = n / d;

    return true;
}
