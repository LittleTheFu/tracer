#include "cball.h"
#include "common.h"
#include <cmath>
#include "frame.h"

CBall::CBall(const Vector3 &rotate, const Vector3 &position, float r, const Rmaterial &mtrl)
{
    init(rotate, position);

    this->r = r;
    this->mtrl = mtrl;
}

Vector3 CBall::getLocalNormal(const Vector3 &point) const
{
    Vector3 normal = point;
    normal.normalize();

    return normal;
}

bool CBall::hit(const Ray &ray, HitRecord &record) const
{
    record.t = Common::FLOAT_MAX;

    const Ray newRay = ray.genNewRay(m_transform);

    const float a = newRay.dir.lenthSqr();
    const float b = 2 * (newRay.dir * newRay.origin);
    const float c = newRay.origin.lenthSqr() - r * r;

    const float delta = b * b - 4 * a * c;

    if (delta <= 0.0f)
        return false;

    float t0 = (-b + sqrt(delta)) / (2 * a);
    float t1 = (-b - sqrt(delta)) / (2 * a);
    float temp = 0;
    if (t0 > t1)
    {
        temp = t0;
        t0 = t1;
        t1 = temp;
    }

    bool hit = t0 > Common::FLOAT_SAMLL_NUMBER;
    record.t = t0;

    if (!hit)
    {
        if (t1 > Common::FLOAT_SAMLL_NUMBER)
        {
            hit = true;
            record.t = t1;
        }
    }

    if (hit)
    {
        const Vector3 localPoint = newRay.origin + record.t * newRay.dir;
        record.point = m_transform.transformPoint(localPoint);

        const Vector3 localNormal = getLocalNormal(localPoint);
        record.normal = m_transform.transformNormal(localNormal);

        Vector3 r = Vector3::sampleUniformFromHemisphere();
        if (r.z == 0)
            r.z = 1;
        if (r.z < 0)
            r.z *= -1;

        Frame frame(localNormal, dpdu(localPoint));

        Vector3 localReflectVector = r.x * frame.x + r.y * frame.y + r.z * frame.z;
        localReflectVector.normalize();
        record.reflect = m_transform.transformVector(localReflectVector);
    }

    return hit;
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

float CBall::getPhi(const Vector3 &point) const
{
    float phi = std::atan2(point.y, point.x);
    if (phi < 0)
    {
        phi += Common::PI * 2;
    }

    return phi;
}

float CBall::getTheta(const Vector3 &point) const
{
    float a = point.z / r;
    if (a < -1)
        a = -1;
    if (a > 1)
        a = 1;

    const float theta = std::acos(point.z / r);

    return theta;
}