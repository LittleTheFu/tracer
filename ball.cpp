#include "ball.h"

Ball::Ball(const Vector3 &center, float r)
{
    this->center = center;
    this->r = r;
}

Vector3 Ball::getCenter() const
{
    return center;
}

Vector3 Ball::getNormal(const Vector3 &point) const
{
    Vector3 normal = point - center;
    normal.normalize();

    return normal;
}