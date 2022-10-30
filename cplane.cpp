#include "cplane.h"
#include "common.h"
#include <cmath>

CPlane::CPlane(const Vector3 &rotate, const Vector3 &position, float length, const Rmaterial &mtrl)
{
    init(rotate, position);

    this->length = length;
    this->mtrl = mtrl;
}

Vector3 CPlane::getLocalNormal() const
{
    return Vector3(0, 0, 1);
}

bool CPlane::hit(const Ray &ray, HitRecord &record) const
{
    record.t = Common::FLOAT_MAX;

    const Ray newRay = ray.genNewRay(m_transform);

    if (newRay.dir * getLocalNormal() >= 0)
    {
        return false;
    }

    const float n = (-newRay.origin) * getLocalNormal();
    const float d = newRay.dir * getLocalNormal();

    record.t = n / d;
    if (record.t < Common::FLOAT_SAMLL_NUMBER)
        return false;

    Vector3 localPoint = newRay.origin + record.t * newRay.dir;

    if (!isLocalIn(localPoint))
    {
        return false;
    }

    record.point = m_transform.transformPoint(localPoint);
    record.normal = m_transform.transformVector(getLocalNormal());

    const Vector3 localReflectVector = Vector3::sampleUniformFromHemisphere();
    record.reflect = m_transform.transformVector(localReflectVector);

    return true;
}

Vector3 CPlane::dpdu(const Vector3 &point) const
{
    return Vector3(1, 0, 0);
}

Vector3 CPlane::dpdv(const Vector3 &point) const
{
    return Vector3(0, 1, 0);
}

bool CPlane::isLocalIn(const Vector3 &p) const
{
    if (!Common::float_equal(p.z, 0))
    {
        return false;
    }

    const float half_length = length / 2;

    const float absX = std::abs(p.x);
    if (absX > half_length)
        return false;

    const float absY = std::abs(p.y);
    if (absY > half_length)
        return false;

    return true;
}
