#include "ray.h"

Ray::Ray(const Vector3 &origin, const Vector3 &dir)
{
    this->origin = origin;
    this->dir = dir;
    this->dir.normalize();
}

bool Ray::hit(const Ball &ball)
{
    const float a = dir.lenthSqr();
    const float b = 2 * (dir * origin - dir * ball.getCenter());
    const float c = origin.lenthSqr() +
                    ball.getCenter().lenthSqr() -
                    2 * (origin * ball.getCenter()) -
                    ball.r * ball.r;

    const float delta = b * b - 4 * a * c;

    if (delta < 0.0f)
        return false;

    const float t0 = (-b + delta) / (2 * a);
    const float t1 = (b + delta) / (2 * a);

    bool hit = t0 > 0.0f;
    if (!hit)
        hit = t1 > 0.0f;

    return hit;
}