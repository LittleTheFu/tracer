#include "ball.h"

Ball::Ball()
{
    center = Vector3(0, 0, 0);
    r = 10;
}

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

void Ball::setPos(float x, float y, float z)
{
    center.x = x;
    center.y = y;
    center.z = z;
}

void Ball::setR(float r)
{
    this->r = r;
}

bool Ball::isInTheBall(const Vector3 &point)
{
    const float distSqr = (point - center).lenthSqr();
    const float diff = distSqr - r * r;

    return diff <= 0.00001;
}

void Ball::setMaterial(const Material &mtrl)
{
    this->mtrl = mtrl;
}
