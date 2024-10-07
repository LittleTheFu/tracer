#include "tri.h"
#include "common.h"
#include <cassert>

// Tri::Tri()
// {
//     m_ab = m_b.pos - m_a.pos;
//     m_bc = m_c.pos - m_b.pos;
//     m_ca = m_a.pos - m_c.pos;
// }

Tri::Tri(const TriVertex &a,
         const TriVertex &b,
         const TriVertex &c,
         const Vector3 &pos,
         Material *pMtrl)
{
    m_a = a;
    m_b = b;
    m_c = c;

    m_ab = m_b.pos - m_a.pos;
    m_bc = m_c.pos - m_b.pos;
    m_ca = m_a.pos - m_c.pos;

    initNormal();

    this->m_pMtrl = pMtrl;

    init(Vector3::ZERO, pos);
}

//transform twice
//1.to object frame
//2.then to tri frame
bool Tri::hit(const Ray &ray, HitRecord &record, Light *pLight) const
{
    record.t = Common::FLOAT_MAX;

    Ray testRay(Vector3(0,0,0), Vector3(0,0,1));

    Ray newRay = ray.genNewRay(m_transform);

    Frame frame(m_normal, m_ab, m_a.pos);
    Ray localRay = newRay.genNewRay(frame);

    // bool reverse = false;
    const Vector3 trueNormal = getLocalNormal(false);
    // if (newRay.dir.isSameDir(trueNormal))
    // {
    //     reverse = true;
    // }
    // else{
    //     reverse = false;
    // }

    const float n = (-localRay.origin) * Common::LOCAL_NORMAL;
    const float d = localRay.dir * Common::LOCAL_NORMAL;

    record.t = n / d;
    if (record.t < Common::FLOAT_SAMLL_NUMBER)
    {
        // std::cout << record.t << "," << n << "," << d << std::endl;
        // std::cout<<"false1"<<std::endl;
        return false;
    }

    Vector3 localPoint = localRay.origin + record.t * localRay.dir;
    Vector3 _objPoint = frame.pointToWorld(localPoint);
    if (!isAllFacePositive(_objPoint))
    {
        return false;
    }

    record.mtrl = *m_pMtrl;
    record.transform = m_transform;

    record.point = m_transform.transformPoint(_objPoint);
    record.normal = m_transform.transformNormal(frame.vectorToWorld(Common::LOCAL_NORMAL));

    // float w_a, w_b, w_c;
    // getWeight(ap_ab, ap_bc, ap_ca, w_a, w_b, w_c);

    // record.u = m_a.u * w_a + m_b.u * w_b + m_c.u * w_c;
    // record.v = m_a.v * w_a + m_b.v * w_b + m_c.v * w_c;

    if (m_pMtrl)
    {
        Vector3 r;
        record.f = m_pMtrl->eval(record.u, record.v, -localRay.dir, r, record.reflectPdf);
        assert(record.f.isValid());
        // float f_dot = r * Common::LOCAL_NORMAL;
        // if(f_dot < 0)
        // {
        //     return false;
        // }
        record.dot = Common::clamp(std::abs(r * Common::LOCAL_NORMAL), Common::FLOAT_SAMLL_NUMBER, 1.0f);
        record.reflect = m_transform.transformVector(frame.vectorToWorld(r));
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
    return m_normal;
    
    // Vector3 n = m_a.normal + m_b.normal + m_c.normal;
    // n.normalize();
    
    // Vector3 n = m_ab.cross(-m_ca);

    // if(reverse)
    // {
    //     n *= -1;
    // }

    // return n;
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

void Tri::initNormal()
{
    // m_normal = m_a.normal + m_b.normal + m_c.normal;
    m_normal = m_ab.cross(m_bc);
    m_normal.normalize();

    // m_normal = Vector3(0,0,-1);
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