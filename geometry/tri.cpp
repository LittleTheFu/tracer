#include "tri.h"
#include "common.h"

Tri::Tri()
{
    m_ab = m_b.pos - m_a.pos;
    m_bc = m_c.pos - m_b.pos;
    m_ca = m_a.pos - m_c.pos;
}

Tri::Tri(const TriVertex &a, const TriVertex &b, const TriVertex &c, Material *pMtrl)
{
    m_a = a;
    m_b = b;
    m_c = c;

    m_ab = m_b.pos - m_a.pos;
    m_bc = m_c.pos - m_b.pos;
    m_ca = m_a.pos - m_c.pos;

    this->m_pMtrl = pMtrl;

    Vector3 pos(0,0,320);
    Vector3 rot(0,0,0);
    init(rot, pos);
}

bool Tri::hit(const Ray &ray, HitRecord &record, Light *pLight) const
{
    record.t = Common::FLOAT_MAX;

    Ray newRay = ray.genNewRay(m_transform);

    // newRay.origin = Vector3(30,30, -300);
    // newRay.dir = Vector3(0,0,1);

    bool reverse = false;
    const Vector3 nm = getLocalNormal(false);
    if (newRay.dir.isSameDir(nm))
    {
        reverse = true;
    }

    const Vector3 trueNormal = getLocalNormal(reverse);
    const float n = (m_a.pos - newRay.origin) * trueNormal;
    const float d = newRay.dir * trueNormal;

    record.t = n / d;
    if (record.t < Common::FLOAT_SAMLL_NUMBER)
    {
        // std::cout << record.t << "," << n << "," << d << std::endl;
        // std::cout<<"false1"<<std::endl;
        return false;
    }

    Vector3 localPoint = newRay.origin + record.t * newRay.dir;
    if (!isAllFacePositive(localPoint))
    {
        // std::cout<<"false2"<<std::endl;
        return false;
    }

    record.mtrl = *m_pMtrl;
    record.transform = m_transform;

    record.point = m_transform.transformPoint(localPoint);
    record.normal = m_transform.transformNormal(trueNormal);

    // float w_a, w_b, w_c;
    // getWeight(ap_ab, ap_bc, ap_ca, w_a, w_b, w_c);

    // record.u = m_a.u * w_a + m_b.u * w_b + m_c.u * w_c;
    // record.v = m_a.v * w_a + m_b.v * w_b + m_c.v * w_c;

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

    // std::cout<<"true"<<std::endl;
    return true;
}

Vector3 Tri::getLocalNormal(bool reverse) const
{
    Vector3 n = m_ab.cross(-m_ca);

    if(reverse)
    {
        n *= -1;
    }

    return n;
}

bool Tri::isAllFacePositive(const Vector3 &p) const
{
    Vector3 ap = p - m_a.pos;
    Vector3 bp = p - m_b.pos;
    Vector3 cp = p - m_c.pos;

    Vector3 bc_bp = m_bc.cross(bp).dir();
    Vector3 ca_cp = m_ca.cross(cp).dir();
    Vector3 ab_ap = m_ab.cross(ap).dir();

    if(bc_bp != ca_cp) return false;
    if(ca_cp != ab_ap) return false;
    if(ab_ap != bc_bp) return false;
    
    return true;
}

Vector3 Tri::dpdu(const Vector3 &point) const
{
    return Vector3();
}

Vector3 Tri::dpdv(const Vector3 &point) const
{
    return Vector3();
}

float Tri::u(const Vector3 &point) const
{
    return 0.0f;
}

float Tri::v(const Vector3 &point) const
{
    return 0.0f;
}