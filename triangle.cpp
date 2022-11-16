#include "triangle.h"
#include "common/common.h"

TriAngleVertex::TriAngleVertex()
{
    x = 0;
    y = 0;

    u = 0;
    v = 0;
}

TriAngleVertex::TriAngleVertex(float x, float y, float u, float v)
{
    this->x = x;
    this->y = y;

    this->u = u;
    this->v = v;
}

TriAngle::TriAngle(const TriAngleVertex &a,
                   const TriAngleVertex &b,
                   const TriAngleVertex &c,
                   const Vector3 &rotate,
                   const Vector3 &position,
                   Material *pMtrl)
{
    init(rotate, position);

    m_a = a;
    m_b = b;
    m_c = c;

    m_pMtrl = pMtrl;
}

Vector3 TriAngle::getLocalNormal(bool reverse = false) const
{
    if (reverse)
    {
        return Vector3(0, 0, -1);
    }

    return Vector3(0, 0, 1);
}

bool TriAngle::hit(const Ray &ray, HitRecord &record) const
{
    record.t = Common::FLOAT_MAX;

    const Ray newRay = ray.genNewRay(m_transform);

    bool reverse = false;
    if (newRay.dir.z >= 0)
    {
        reverse = true;
    }

    const float n = (-newRay.origin) * getLocalNormal(reverse);
    const float d = newRay.dir * getLocalNormal(reverse);

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
    record.normal = m_transform.transformNormal(getLocalNormal(reverse));

    // record.u = u(localPoint);
    // record.v = v(localPoint);

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

bool TriAngle::isLocalIn(const Vector3 &p) const
{
    Vector3 a = Vector3(m_a.x, m_a.y, 0);
    Vector3 b = Vector3(m_b.x, m_b.y, 0);
    Vector3 c = Vector3(m_c.x, m_c.y, 0);

    Vector3 ap = p - a;
    Vector3 bp = p - b;
    Vector3 cp = p - c;

    Vector3 ab = b - a;
    Vector3 bc = c - b;
    Vector3 ca = a - c;

    Vector3 va = ap.cross(ab);
    Vector3 vb = bp.cross(bc);
    Vector3 vc = cp.cross(ca);

    bool flagA = va.z < 0;
    bool flagB = vb.z < 0;
    bool flagC = vc.z < 0;

    bool flag = (flagA && flagB && flagC);

    if (flag)
    {
        int vvv = 0;
    }
    else
    {
        int www = 0;
    }

    return flag;
}

Vector3 TriAngle::dpdu(const Vector3 &point) const
{
    return Vector3::ZERO;
}

Vector3 TriAngle::dpdv(const Vector3 &point) const
{
    return Vector3::ZERO;
}

float TriAngle::u(const Vector3 &point) const
{
    return 0;
}

float TriAngle::v(const Vector3 &point) const
{
    return 0;
}