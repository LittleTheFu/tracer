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