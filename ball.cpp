#include "ball.h"
#include <cmath>
#include "common.h"

Ball::Ball()
{
    center = Vector3(0, 0, 0);
    r = 10;
}

Ball::Ball(const Vector3 &center, float r)
{
    this->center = center;
    this->r = r;

    transform.translate(center.x, center.y, center.z);
}

Vector3 Ball::getLocalCenter() const
{
    return Vector3(0, 0, 0);
}

Vector3 Ball::getLocalNormal(const Vector3 &point) const
{
    Vector3 normal = point - getLocalCenter();
    normal.normalize();

    return normal;
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

    transform.translate(x, y, z);
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

float Ball::getPhi(const Vector3 &p) const
{
    float phi = std::atan2(p.y, p.x);
    if (phi < 0)
    {
        phi += Common::PI * 2;
    }

    return phi;
}

float Ball::getTheta(const Vector3 &p) const
{
    float a = p.z / r;
    if (a < -1)
        a = -1;
    if (a > 1)
        a = 1;

    const float theta = std::acos(p.z / r);

    return theta;
}

Vector3 Ball::dpdu(const Vector3 &p) const
{
    // const float phi = getPhi(p);
    const float phi_max = Common::PI * 2;

    const float x = -p.y * phi_max;
    const float y = p.x * phi_max;
    const float z = 0;

    Vector3 v = Vector3(x, y, z);
    v.normalize();

    return v;
}

Vector3 Ball::dpdv(const Vector3 &p) const
{
    const float phi = getPhi(p);
    const float theta_range = Common::PI;

    const float theta = getTheta(p);

    const float x = p.z * std::cos(phi) * theta_range;
    const float y = p.z * std::sin(phi) * theta_range;
    const float z = -std::sin(theta) * theta_range;

    Vector3 v = Vector3(x, y, z);
    v.normalize();

    return v;
}
