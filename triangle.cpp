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

    float ab_x = b.x - a.x;
    float ab_y = b.y - a.y;
    float ac_x = c.x - a.x;
    float ac_y = c.y - a.y;

    m_doulbe_area = std::abs(ab_x * ac_y - ac_x * ab_y);
}

Vector3 TriAngle::getLocalNormal(bool reverse = false) const
{
    if (reverse)
    {
        return Vector3(0, 0, -1);
    }

    return Vector3(0, 0, 1);
}

bool TriAngle::hit(const Ray &ray, HitRecord &record, Light *pLight) const
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
    Vector3 ap_ab;
    Vector3 ap_bc;
    Vector3 ap_ca;
    getCrossResult(localPoint, ap_ab, ap_bc, ap_ca);

    if (!isAllFacePositive(ap_ab, ap_bc, ap_ca))
    {
        return false;
    }

    record.mtrl = *m_pMtrl;
    record.transform = m_transform;

    record.point = m_transform.transformPoint(localPoint);
    record.normal = m_transform.transformNormal(getLocalNormal(reverse));

    float w_a, w_b, w_c;
    getWeight(ap_ab, ap_bc, ap_ca, w_a, w_b, w_c);

    record.u = m_a.u * w_a + m_b.u * w_b + m_c.u * w_c;
    record.v = m_a.v * w_a + m_b.v * w_b + m_c.v * w_c;

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

void TriAngle::getCrossResult(const Vector3 &p,
                              Vector3 &apCrossAb,
                              Vector3 &apCrossBc,
                              Vector3 &apCrossCa) const
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

    apCrossAb = ap.cross(ab);
    apCrossBc = bp.cross(bc);
    apCrossCa = cp.cross(ca);
}

bool TriAngle::isAllFacePositive(const Vector3 &a, const Vector3 &b, const Vector3 &c) const
{
    // Vector3 a = Vector3(m_a.x, m_a.y, 0);
    // Vector3 b = Vector3(m_b.x, m_b.y, 0);
    // Vector3 c = Vector3(m_c.x, m_c.y, 0);

    // Vector3 ap = p - a;
    // Vector3 bp = p - b;
    // Vector3 cp = p - c;

    // Vector3 ab = b - a;
    // Vector3 bc = c - b;
    // Vector3 ca = a - c;

    // Vector3 va = ap.cross(ab);
    // Vector3 vb = bp.cross(bc);
    // Vector3 vc = cp.cross(ca);

    bool flagA = a.z < 0;
    bool flagB = b.z < 0;
    bool flagC = c.z < 0;

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

void TriAngle::getWeight(const Vector3 &ap_ab,
                         const Vector3 &ap_bc,
                         const Vector3 &ap_ca,
                         float &weightA,
                         float &weightB,
                         float &weightC) const
{
    float double_area_pab = ap_ab.length();
    float double_area_pbc = ap_bc.length();
    float double_area_pca = ap_ca.length();

    weightA = double_area_pbc / m_doulbe_area;
    weightB = double_area_pca / m_doulbe_area;
    weightC = double_area_pab / m_doulbe_area;
}