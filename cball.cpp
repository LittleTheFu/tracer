#include "cball.h"
#include "common.h"
#include <cmath>
#include "frame.h"

CBall::CBall(const Vector3 &rotate, const Vector3 &position, float r, Rmaterial *pMtrl)
{
    init(rotate, position);

    this->r = r;
    this->m_pMtrl = pMtrl;
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
        record.mtrl = *m_pMtrl;
        record.transform = m_transform;

        const Vector3 localPoint = newRay.origin + record.t * newRay.dir;
        record.point = m_transform.transformPoint(localPoint);

        const Vector3 localNormal = getLocalNormal(localPoint);
        record.normal = m_transform.transformNormal(localNormal);

        if (m_pMtrl->pBrdf)
        {
            Vector3 r;
            record.f = m_pMtrl->pBrdf->sample_f(newRay.dir, r, record.reflectPdf);
            record.dot = Common::clamp(r * Common::LOCAL_NORMAL, Common::FLOAT_SAMLL_NUMBER, 1.0f);
            if (r.z == 0)
                r.z = 1;
            if (r.z < 0)
                r.z *= -1;

            Frame frame(localNormal, dpdu(localPoint));

            Vector3 localReflectVector = r.x * frame.x + r.y * frame.y + r.z * frame.z;
            localReflectVector.normalize();
            record.reflect = m_transform.transformVector(localReflectVector);
        }
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