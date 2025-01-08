#include <cassert>

#include "common.h"
#include "mathConstantDef.h"
#include "mathUtility.h"
#include "tri.h"

Tri::Tri()
{
}

Tri::Tri(const TriVertex &a,
         const TriVertex &b,
         const TriVertex &c,
         const Vector3 &pos,
         std::shared_ptr<Material> material)
{
    set(a, b, c, pos, material);
}

void Tri::set(const TriVertex &a, const TriVertex &b, const TriVertex &c, const Vector3 &pos, std::shared_ptr<Material> material)
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

// transform three times
// 1.to object frame
// 2.then to tri frame built from face normal
// 3.then to tri frame built from weighted normal
bool Tri::hit(const Ray &ray, HitRecord &record) const
{
    record.t = MathConstant::FLOAT_MAX;
    Ray newRay = ray.genNewRay(m_transform);

    Frame frame(m_normal, m_ab, m_a.pos);
    Ray localRay = newRay.genNewRay(frame);

    if (!testHit(localRay, record.t))
        return false;

    //reduntant code,refactor later...
    Vector3 localPoint = localRay.origin + record.t * localRay.dir;
    Vector3 _objPoint = frame.pointToWorld(localPoint);

    Vector3 pixelNormal = getWeightedNormal(_objPoint);
    //quick and dirty,need to refactor and optimized later...
    //and some variable should be renamed
    if(m_pMtrl && m_pMtrl->isNormalTextureValid()) 
    {
        //to be optimized later...
        pixelNormal = m_pMtrl->getNormalTexture()->getNormal(u(_objPoint), v(_objPoint));
        pixelNormal = frame.vectorToWorld(pixelNormal);
    }
    Frame pixelFrame(pixelNormal, m_ab, _objPoint);
    Vector3 weghtedRayDir = pixelFrame.vectorToLocal(frame.vectorToWorld(localRay.dir));

    record.transform = m_transform;
    record.point = m_transform.transformPoint(_objPoint);

    record.u = u(_objPoint);
    record.v = v(_objPoint);

    record.normal = m_transform.transformNormal(pixelFrame.vectorToWorld(Common::LOCAL_NORMAL));

    if (m_pMtrl)
    {
        Vector3 r;
        record.f = m_pMtrl->eval(record.u, record.v, -weghtedRayDir, r, record.reflectPdf, record.isDelta, record.brdf);

        record.dot = MathUtility::clamp(std::abs(r * Common::LOCAL_NORMAL), 0.0f, 1.0f);
        record.reflect = m_transform.transformVector(pixelFrame.vectorToWorld(r));

        if (record.isDelta)
        {
            record.dot = 1;
        }
    }

    return true;
}

bool Tri::testHit(const Ray &localRay, float &t) const
{
    const float n = (-localRay.origin) * Common::LOCAL_NORMAL;
    const float d = localRay.dir * Common::LOCAL_NORMAL;

    t = n / d;
    if (t < MathConstant::FLOAT_SMALL_NUMBER)
        return false;

    Vector3 localPoint = localRay.origin + t * localRay.dir;

    //refactor later...
    Frame frame(m_normal, m_ab, m_a.pos);
    Vector3 _objPoint = frame.pointToWorld(localPoint);
    if (!isAllFacePositive(_objPoint))
        return false;

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

bool Tri::isAllFacePositive(const Vector3 &p) const
{
    Vector3 ap = p - m_a.pos;
    Vector3 bp = p - m_b.pos;
    Vector3 cp = p - m_c.pos;

    Vector3 bc_bp = m_bc.cross(bp);
    Vector3 ca_cp = m_ca.cross(cp);
    Vector3 ab_ap = m_ab.cross(ap);

    if (!bc_bp.isSameDir(ca_cp))
        return false;
    if (!ca_cp.isSameDir(ab_ap))
        return false;
    if (!ab_ap.isSameDir(bc_bp))
        return false;

    return true;
}

void Tri::getWeight(const Vector3 &p, float &wa, float &wb, float &wc) const
{
    wa = 0.0f;
    wb = 0.0f;
    wc = 0.0f;

    // can be optimized with this function,do it later,maybe...
    if (!isAllFacePositive(p))
        return;

    Vector3 ap = p - m_a.pos;
    Vector3 bp = p - m_b.pos;
    Vector3 cp = p - m_c.pos;

    float d = m_ab.cross(m_bc).length();
    if (d == 0.0f)
        return;

    float a = m_bc.cross(bp).length();
    float b = m_ca.cross(cp).length();
    float c = m_ab.cross(ap).length();

    wa = a / d;
    wb = b / d;
    wc = c / d;
}

void Tri::calcNormal()
{
    m_normal = m_ab.cross(m_bc);
    m_normal.normalize();
    // m_normal = m_a.normal + m_b.normal + m_c.normal;
    // m_normal.normalize();
}

Vector3 Tri::getWeightedNormal(const Vector3 &p) const
{
    float wa, wb, wc;
    getWeight(p, wa, wb, wc);

    Vector3 normal = m_a.normal * wa + m_b.normal * wb + m_c.normal * wc;
    normal.normalize();

    return normal;
}

//can be optimized together with getWeightedNormal()
// void Tri::getWeightedUV(const Vector3 &p, float &u, float &v) const
// {
//     float wa, wb, wc;
//     getWeight(p, wa, wb, wc);

//     u = m_a.u * wa + m_b.u * wb + m_c.u * wc;
//     v = m_a.v * wa + m_b.v * wb + m_c.v * wc;
// }

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
    float wa, wb, wc;
    getWeight(point, wa, wb, wc);

    return m_a.u * wa + m_b.u * wb + m_c.u * wc;
}

float Tri::v(const Vector3 &point) const
{
    float wa, wb, wc;
    getWeight(point, wa, wb, wc);

    return m_a.v * wa + m_b.v * wb + m_c.v * wc;
}