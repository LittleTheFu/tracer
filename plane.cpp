#include "plane.h"
#include "common.h"
#include <cmath>
#include <iostream>

Plane::Plane(const Vector3 &rotate, const Vector3 &position, float length, Material *pMtrl)
{
    init(rotate, position);

    this->length = length;
    this->m_pMtrl = pMtrl;
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

    if (m_pMtrl && m_pMtrl->pBrdf)
    {
        Vector3 r;
        record.f = m_pMtrl->pBrdf->sample_f(-newRay.dir, r, record.reflectPdf);
        if (r * Common::LOCAL_NORMAL < 0)
        {
            // m_pMtrl->pBrdf->sample_f(-newRay.dir, r, record.reflectPdf);
            // std::cout << "less" << std::endl;
        }
        record.dot = Common::clamp(std::abs(r * Common::LOCAL_NORMAL), Common::FLOAT_SAMLL_NUMBER, 1.0f);
        record.reflect = m_transform.transformVector(r);
        record.isMirror = m_pMtrl->pBrdf->isMirror();

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

bool Plane::isLocalIn(const Vector3 &p) const
{
    // bug, fix later
    return true;

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