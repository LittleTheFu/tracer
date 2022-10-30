#include "cball.h"
#include "common.h"
#include <cmath>

bool CBall::hit(const Ray &ray, HitRecord &record) const
{
    return false;
}

Vector3 CBall::dpdu(const Vector3 &point) const
{
    const float phi_max = Common::PI * 2;

    const float x = -point.y * phi_max;
    const float y = point.x * phi_max;
    const float z = 0;

    Vector3 v = Vector3(x, y, z);
    v.normalize();

    return v;
}

Vector3 CBall::dpdv(const Vector3 &point) const
{
    const float phi = getPhi(point);
    const float theta_range = Common::PI;

    const float theta = getTheta(point);

    const float x = point.z * std::cos(phi) * theta_range;
    const float y = point.z * std::sin(phi) * theta_range;
    const float z = -std::sin(theta) * theta_range;

    Vector3 v = Vector3(x, y, z);
    v.normalize();

    return v;
}

float Ball::getPhi(const Vector3 &point) const
{
    float phi = std::atan2(point.y, point.x);
    if (phi < 0)
    {
        phi += Common::PI * 2;
    }

    return phi;
}

float Ball::getTheta(const Vector3 &point) const
{
    float a = point.z / r;
    if (a < -1)
        a = -1;
    if (a > 1)
        a = 1;

    const float theta = std::acos(point.z / r);

    return theta;
}