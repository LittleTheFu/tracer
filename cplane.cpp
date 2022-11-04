#include "cplane.h"
#include "common.h"
#include <cmath>
#include <iostream>

CPlane::CPlane(const Vector3 &rotate, const Vector3 &position, float length, Rmaterial *pMtrl)
{
    init(rotate, position);

    this->length = length;
    this->m_pMtrl = pMtrl;
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
    {
        // std::cout << record.t << "," << n << "," << d << std::endl;
        return false;
    }

    Vector3 localPoint = newRay.origin + record.t * newRay.dir;

    if (!isLocalIn(localPoint))
    {
        return false;
    }

    record.mtrl = *m_pMtrl;
    record.transform = m_transform;

    record.point = m_transform.transformPoint(localPoint);
    record.normal = m_transform.transformVector(getLocalNormal());

    if (m_pMtrl && m_pMtrl->pBrdf)
    {
        Vector3 r;
        record.f = m_pMtrl->pBrdf->sample_f(-newRay.dir, r, record.reflectPdf);
        record.dot = Common::clamp(r * Common::LOCAL_NORMAL, Common::FLOAT_SAMLL_NUMBER, 1.0f);
        record.reflect = m_transform.transformVector(r);
    }

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