#include "tri.h"
#include "common.h"
#include "mathUtility.h"
#include "mathConstantDef.h"
#include <cassert>

#define _NORMAL_DEBUG_ (0)

Tri::Tri()
{
}

Tri::Tri(const TriVertex &a,
         const TriVertex &b,
         const TriVertex &c,
         const Vector3 &pos,
         const std::shared_ptr<Material> material)
{
    set(a, b, c, pos, material);
}

void Tri::set(const TriVertex &a, const TriVertex &b, const TriVertex &c, const Vector3 &pos, const std::shared_ptr<Material> material)
{
    m_a = a;
    m_b = b;
    m_c = c;

    m_ab = m_b.pos - m_a.pos;
    m_bc = m_c.pos - m_b.pos;
    m_ca = m_a.pos - m_c.pos;

    calcNormal();

    m_localCentroid = (a.pos + b.pos + c.pos) / 3;
    this->m_pMtrl = material;

    init(Vector3::ZERO, pos);
}

void Tri::getSplitChildren(Tri *outTri_1, Tri *outTri_2, Tri *outTri_3) const
{
    Vector3 centroid = (m_a.pos + m_b.pos + m_c.pos) / 3;
    TriVertex d(centroid, Vector3::ZERO);

    outTri_1->setTransform(m_transform);
    outTri_1->set(m_a, m_b, d, m_pos, m_pMtrl);

    outTri_2->setTransform(m_transform);
    outTri_2->set(m_b, m_c, d, m_pos, m_pMtrl);

    outTri_3->setTransform(m_transform);
    outTri_3->set(m_c, m_a, d, m_pos, m_pMtrl);
}

//transform twice
//1.to object frame
//2.then to tri frame
bool Tri::hit(const Ray &ray, HitRecord &record) const
{
    record.t = MathConstant::FLOAT_MAX;

    Ray testRay(Vector3(0,0,0), Vector3(0,0,1));
    Ray newRay = ray.genNewRay(m_transform);

    Frame frame(m_normal, m_ab, m_a.pos);
    Ray localRay = newRay.genNewRay(frame);

    const Vector3 trueNormal = getLocalNormal(false);
    const float n = (-localRay.origin) * Common::LOCAL_NORMAL;
    const float d = localRay.dir * Common::LOCAL_NORMAL;

    record.t = n / d;
    if (record.t < MathConstant::FLOAT_SAMLL_NUMBER)
    {
        return false;
    }

    Vector3 localPoint = localRay.origin + record.t * localRay.dir;
    Vector3 _objPoint = frame.pointToWorld(localPoint);
    if (!isAllFacePositive(_objPoint))
    {
        return false;
    }

    record.mtrl = m_pMtrl;
    record.transform = m_transform;

    record.point = m_transform.transformPoint(_objPoint);

#if _NORMAL_DEBUG_
    record.normal = m_transform.transformVector(frame.vectorToWorld(Common::LOCAL_NORMAL));
#else
    record.normal = m_transform.transformNormal(frame.vectorToWorld(Common::LOCAL_NORMAL));
#endif

    // float w_a, w_b, w_c;
    // getWeight(ap_ab, ap_bc, ap_ca, w_a, w_b, w_c);

    // record.u = m_a.u * w_a + m_b.u * w_b + m_c.u * w_c;
    // record.v = m_a.v * w_a + m_b.v * w_b + m_c.v * w_c;

    if (m_pMtrl)
    {
        Vector3 r;
        record.f = m_pMtrl->eval(record.u, record.v, -localRay.dir, r, record.reflectPdf, record.isDelta);
        assert(record.f.isValid());
 
        record.dot = MathUtility::clamp(std::abs(r * Common::LOCAL_NORMAL), MathConstant::FLOAT_SAMLL_NUMBER, 1.0f);
        record.reflect = m_transform.transformVector(frame.vectorToWorld(r));

        if (record.isDelta)
        {
            record.dot = 1;
        }
    }
    else
    {
        record.insideMedia = m_insideMedia;
        record.outsideMedia = m_outsideMedia;
    }

    // std::cout<<"true"<<std::endl;
    return true;
}

Vector3 Tri::getCentroid() const
{
    return m_transform.transformPoint(m_localCentroid);
}

float Tri::surfaceArea() const
{
    float ab = m_ab.length();
    float ac = m_ca.length();

    return ab * ac * 0.5f;
}

void Tri::buildBoundBox()
{
    Vector3 a = m_transform.transformPoint(m_a.pos);
    Vector3 b = m_transform.transformPoint(m_b.pos);
    Vector3 c = m_transform.transformPoint(m_c.pos);

    m_boundBox.update(a);
    m_boundBox.update(b);
    m_boundBox.update(c);
}

Vector3 Tri::getLocalNormal(bool reverse) const
{
    return m_normal;
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

void Tri::calcNormal()
{
    m_normal = m_ab.cross(m_bc);
    m_normal.normalize();
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