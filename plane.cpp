#include "plane.h"
#include "common.h"
#include <cmath>
#include <iostream>

Plane::Plane(const Vector3 &rotate, const Vector3 &position, float length, Material *pMtrl)
{
    init(rotate, position);

    this->length = length;
    this->m_pMtrl = pMtrl;

    this->m_uvCellSize = 400;
}

Vector3 Plane::getLocalNormal() const
{
    return Vector3(0, 0, 1);
}

bool Plane::hit(const Ray &ray, HitRecord &record) const
{
    record.t = Common::FLOAT_MAX;

    const Ray newRay = ray.genNewRay(m_transform);

    // if (newRay.dir * getLocalNormal() >= 0)
    if (newRay.dir.z >= 0)
    {
        return false;
    }

    const float n = (-newRay.origin) * getLocalNormal();
    const float d = newRay.dir * getLocalNormal();

    record.t = n / d;
    if (record.t < Common::FLOAT_SAMLL_NUMBER)
    {
        // std::cout << record.t << "," << n << "," << d << std::endl;
        return false;
    }

    Vector3 localPoint = newRay.origin + record.t * newRay.dir;

    if (!isLocalIn(localPoint))
    {
        // some bug here
        return false;
    }

    record.mtrl = *m_pMtrl;
    record.transform = m_transform;

    record.point = m_transform.transformPoint(localPoint);
    record.normal = m_transform.transformNormal(getLocalNormal());

    record.u = u(localPoint);
    record.v = v(localPoint);

    if (m_pMtrl)
    {
        Vector3 r;
        record.f = m_pMtrl->eval(record.u, record.v, -newRay.dir, r, record.reflectPdf);
        record.dot = Common::clamp(std::abs(r * Common::LOCAL_NORMAL), Common::FLOAT_SAMLL_NUMBER, 1.0f);
        record.reflect = m_transform.transformVector(r);
        record.isMirror = m_pMtrl->isMirror();

        if (record.isMirror)
        {
            record.dot = 1;
        }
    }

    return true;
}

Vector3 Plane::dpdu(const Vector3 &point) const
{
    return Vector3(1, 0, 0);
}

Vector3 Plane::dpdv(const Vector3 &point) const
{
    return Vector3(0, 1, 0);
}

float Plane::u(const Vector3 &point) const
{
    float rawU = point.x / m_uvCellSize;
    float uu = rawU - (int)rawU;

    return uu;
}

float Plane::v(const Vector3 &point) const
{
    float rawV = point.y / m_uvCellSize;
    float vv = rawV - (int)rawV;

    return vv;
}

bool Plane::isLocalIn(const Vector3 &p) const
{
    // bug, fix later
    return true;

    if (!Common::is_float_equal(p.z, 0))
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