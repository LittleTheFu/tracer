#include <cassert>

#include "boundBox.h"
#include "curve.h"
#include "mathUtility.h"
#include "materialManager.h"

const int Curve::CONTROL_POINTS_NUM = 4;
const int Curve::MAX_DEPTH = 100;

Curve::Curve(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3)
{
    m_p0 = p0;
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;

    m_width = 1.0f;

    //test
    m_pMtrl = MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED);
}

void Curve::setWidth(float width)
{
    m_width = width;
}

bool Curve::hit(const Ray &ray, HitRecord &record) const
{
    // const Ray newRay = ray.genNewRay(m_transform);
    const Ray newRay = ray; // test

    float t0 = 0.0f;
    float t1 = 0.0f;
    bool isHit = hitRecursive(newRay, record, MAX_DEPTH, t0, t1);

    return isHit;
}

void Curve::buildBoundBox()
{
    m_boundBox.update(m_p0);
    m_boundBox.update(m_p1);
    m_boundBox.update(m_p2);
    m_boundBox.update(m_p3);
}

Vector3 Curve::dpdu(const Vector3 &point) const
{
    return Vector3();
}

Vector3 Curve::dpdv(const Vector3 &point) const
{
    return Vector3();
}

float Curve::u(const Vector3 &point) const
{
    return 0.0f;
}

float Curve::v(const Vector3 &point) const
{
    return 0.0f;
}

bool Curve::hitRecursive(const Ray &ray,
                         HitRecord &record,
                         int depth,
                         float t0,
                         float t1) const
{
    std::vector<Vector3> controlPoints = {m_p0, m_p1, m_p2, m_p3};
    return _hitRecursive(ray, record, depth, controlPoints);
}

bool Curve::_hitRecursive(const Ray &ray,
                          HitRecord &record,
                          int depth,
                          const std::vector<Vector3> &controlPoints) const
{
    if (depth <= 0)
        return hitCurveSegment(ray, record, controlPoints);

    std::vector<Vector3> left, right;
    split(left, right);
    assert(left.size() == CONTROL_POINTS_NUM);
    assert(right.size() == CONTROL_POINTS_NUM);

    bool isLeftHit = hitBoundBox(ray, left);
    bool isRightHit = hitBoundBox(ray, right);

    if(isLeftHit)
    {
        int a = 3;
    }

    if(isRightHit)
    {
        int a = 3;
    }

    if (isLeftHit)
        return _hitRecursive(ray, record, depth - 1, left);

    if (isRightHit)
        return _hitRecursive(ray, record, depth - 1, right);

    return false;
}

bool Curve::hitBoundBox(const Ray &ray, const std::vector<Vector3> &controlPoints) const
{
    assert(controlPoints.size() == CONTROL_POINTS_NUM);

    BoundBox boundBox;
    for (int i = 0; i < CONTROL_POINTS_NUM; ++i)
    {
        boundBox.update(controlPoints[i]);
    }

    float dummyT = 0.0f;
    bool isHit = boundBox.hit(ray, dummyT);

    return isHit;
}

bool Curve::hitCurveSegment(const Ray &ray, HitRecord &record, const std::vector<Vector3> &controlPoints) const
{
    assert(controlPoints.size() == CONTROL_POINTS_NUM);

    Vector3 tangentStart = controlPoints.at(1) - controlPoints.at(0);
    Vector3 orthogonalStart = tangentStart.getTangentVector();

    Vector3 tangentEnd = controlPoints.at(2) + controlPoints.at(3);
    Vector3 orthogonalEnd = tangentEnd.getTangentVector();

    Vector3 v = orthogonalStart + orthogonalEnd;
    v.normalize();

    Vector3 u = controlPoints.at(3) - controlPoints.at(0);
    u.normalize();

    Vector3 normal = v.cross(u);
    normal.normalize();

    float t = (controlPoints.at(0) - ray.origin) * normal / (ray.dir * normal);
    Vector3 point = ray.getPosition(t);

    Vector3 p0 = controlPoints.at(0) - 0.5f * v * m_width;
    Vector3 p1 = controlPoints.at(0) + 0.5f * v * m_width;

    Vector3 p2 = controlPoints.at(2) - 0.5f * v * m_width;
    Vector3 p3 = controlPoints.at(2) + 0.5f * v * m_width;

    Vector3 p0p1 = p1 - p0;
    Vector3 p1p2 = p2 - p1;
    Vector3 p2p3 = p3 - p2;
    Vector3 p3p0 = p0 - p3;

    Vector3 p_p0 = point - p0;
    Vector3 p_p1 = point - p1;
    Vector3 p_p2 = point - p2;
    Vector3 p_p3 = point - p3;

    Vector3 cross0 = p_p0.cross(p0p1);
    Vector3 cross1 = p_p1.cross(p1p2);
    Vector3 cross2 = p_p2.cross(p2p3);
    Vector3 cross3 = p_p3.cross(p3p0);

    // if (!cross0.isSameDir(cross1))
    //     return false;
    // if (!cross1.isSameDir(cross2))
    //     return false;
    // if (!cross2.isSameDir(cross3))
    //     return false;
    // if (!cross3.isSameDir(cross0))
    //     return false;

    record.t = t;
    // record.brdf = m_pMtrl->getBrdf()->clone();
    // m_pMtrl->eval(record.brdf, record.f, record.dot, record.dotLight, record.normal, record.outsideMedia, record.insideMedia, record.isDelta, record.isMistHit, record.isVolumeBoundery, record.transform, record.u, record.v);
    record.f = m_pMtrl->eval(record.u, record.v, -ray.dir, record.reflect, record.reflectPdf, record.isDelta, record.brdf);

    return true;
}

void Curve::split(std::vector<Vector3> &left, std::vector<Vector3> &right) const
{
    Vector3 a0 = (m_p0 + m_p1) / 2.0f;
    Vector3 a1 = (m_p1 + m_p2) / 2.0f;
    Vector3 a2 = (m_p2 + m_p3) / 2.0f;

    Vector3 b0 = (a0 + a1) / 2.0f;
    Vector3 b1 = (a1 + a2) / 2.0f;

    Vector3 c0 = (b0 + b1) / 2.0f;

    // for clarity
    Vector3 left0 = m_p0;
    Vector3 left1 = a0;
    Vector3 left2 = b0;
    Vector3 left3 = c0;

    Vector3 right0 = c0;
    Vector3 right1 = b1;
    Vector3 right2 = a2;
    Vector3 right3 = m_p3;

    left.push_back(left0);
    left.push_back(left1);
    left.push_back(left2);
    left.push_back(left3);

    right.push_back(right0);
    right.push_back(right1);
    right.push_back(right2);
    right.push_back(right3);
}

Vector3 Curve::getPoint(float u, const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3)
{
    assert(MathUtility::is_in_range(u, 0.0f, 1.0f, true, true));
    Vector3 point = (1 - u) * (1 - u) * (1 - u) * p0 + 3 * (1 - u) * (1 - u) * u * p1 + 3 * (1 - u) * u * u * p2 + u * u * u * p3;

    return point;
}
