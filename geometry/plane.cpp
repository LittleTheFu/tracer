#include "plane.h"
#include "common.h"
#include "mathUtility.h"
#include "mathConstantDef.h"
#include <cmath>
#include <iostream>
Plane::Plane(const Vector3 &rotate, const Vector3 &position, float length, std::shared_ptr<const Material> pMtrl)
{
    init(rotate, position);

    this->half_length = length;
    this->m_pMtrl = pMtrl;

    this->m_uvCellSize = 100;
}

Vector3 Plane::getLocalNormal(bool reverse = false) const
{
    if (reverse)
    {
        return Vector3(0, 0, -1);
    }

    return Vector3(0, 0, 1);
}


bool Plane::hit(const Ray &ray, HitRecord &record) const
{
    record.t = MathConstant::FLOAT_MAX;

    const Ray newRay = ray.genNewRay(m_transform);

    bool reverse = false;
    // if (newRay.dir * getLocalNormal() >= 0)
    if (newRay.dir.z >= 0)
    {
        reverse = true;
    }

    const float n = (-newRay.origin) * getLocalNormal(reverse);
    const float d = newRay.dir * getLocalNormal(reverse);

    record.t = n / d;
    if (record.t < MathConstant::FLOAT_SAMLL_NUMBER)
    {
        // std::cout << record.t << "," << n << "," << d << std::endl;
        return false;
    }

    Vector3 localPoint = newRay.origin + record.t * newRay.dir;

    if (!isLocalIn(localPoint))
    {
        return false;
    }

    record.mtrl = m_pMtrl;
    record.transform = m_transform;

    record.point = m_transform.transformPoint(localPoint);
    record.normal = m_transform.transformNormal(getLocalNormal(reverse));

    record.u = u(localPoint);
    record.v = v(localPoint);

    if (m_pMtrl)
    {
        HandleMaterial(newRay, record);
    }

    return true;
}

Vector3 Plane::getCentroid() const
{
    return m_transform.transformPoint(Vector3::ZERO);
}

float Plane::surfaceArea() const
{
    float length = half_length * 2;
    return length * length;
}

void Plane::buildBoundBox()
{
    Vector3 localPa(-half_length, -half_length, 0);
    Vector3 localPb(-half_length, half_length, 0);
    Vector3 localPc(half_length, -half_length, 0);
    Vector3 localPd(half_length, half_length, 0);

    Vector3 pa = m_transform.transformPoint(localPa);
    Vector3 pb = m_transform.transformPoint(localPb);
    Vector3 pc = m_transform.transformPoint(localPc);
    Vector3 pd = m_transform.transformPoint(localPd);

    m_boundBox.update(pa);
    m_boundBox.update(pb);
    m_boundBox.update(pc);
    m_boundBox.update(pd);
}

void Plane::HandleMaterial(const Ray &newRay, HitRecord &record) const
{
    record.isDelta = m_pMtrl->isDelta();

    Vector3 r;
    record.f = m_pMtrl->eval(record.u, record.v, -newRay.dir, r, record.reflectPdf);
    record.dot = MathUtility::clamp(std::abs(r * Common::LOCAL_NORMAL), MathConstant::FLOAT_SAMLL_NUMBER, 1.0f);
    record.reflect = m_transform.transformVector(r);
    record.isMirror = m_pMtrl->isMirror();

    if (record.isDelta)
    {
        record.dot = 1;
    }
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
    // float x = std::abs(point.x);
    // float modU = (int)x % m_uvCellSize;
    // float uu = modU / (float)m_uvCellSize;

    float x = point.x + half_length;
    float length = half_length * 2;
    float uu = x / length;

    return MathUtility::clamp(std::abs(uu), 0, 1);
}

float Plane::v(const Vector3 &point) const
{
    // float y = std::abs(point.y);
    // float modV = (int)y % m_uvCellSize;
    // float vv = modV / (float)m_uvCellSize;

    float y = point.y + half_length;
    float length = half_length * 2;
    float vv = y / length;

    return MathUtility::clamp(std::abs(vv), 0, 1);
}

bool Plane::isLocalIn(const Vector3 &p) const
{
    if (!MathUtility::is_float_equal(p.z, 0))
    {
        return false;
    }

    const float absX = std::abs(p.x);
    if (absX > half_length)
        return false;

    const float absY = std::abs(p.y);
    if (absY > half_length)
        return false;

    return true;
}