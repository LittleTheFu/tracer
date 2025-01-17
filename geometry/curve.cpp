#include <cassert>

#include "boundBox.h"
#include "curve.h"
#include "mathUtility.h"

const int Curve::CONTROL_POINTS_NUM = 4;
const int Curve::MAX_DEPTH = 10;

Curve::Curve(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3)
{
    m_p0 = p0;
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;

    m_width = 10.0f;
}

void Curve::setWidth(float width)
{
    m_width = width;
}

bool Curve::hit(const Ray &ray, HitRecord &record) const
{
    const Ray newRay = ray.genNewRay(m_transform);

    float t0 = 0.0f;
    float t1 = 0.0f;
    bool isHit = hitRecursive(newRay, record, MAX_DEPTH, t0, t1);

    return false;
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
    std::vector<Vector3> controlPoints = { m_p0, m_p1, m_p2, m_p3 };
    return _hitRecursive(ray, depth, controlPoints);
}

bool Curve::_hitRecursive(const Ray &ray, int depth, const std::vector<Vector3> &controlPoints) const
{
    if (depth <= 0)
        return hitCurveSegment(ray, controlPoints);

    std::vector<Vector3> left, right;
    split(left, right);
    assert(left.size() == CONTROL_POINTS_NUM);
    assert(right.size() == CONTROL_POINTS_NUM);

    bool isLeftHit = hitBoundBox(ray, left);
    bool isRightHit = hitBoundBox(ray, right);

    if(isLeftHit)
        return _hitRecursive(ray, depth - 1, left);

    if(isRightHit)
        return _hitRecursive(ray, depth - 1, right);

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

bool Curve::hitCurveSegment(const Ray &ray, const std::vector<Vector3> &controlPoints) const
{
    assert(controlPoints.size() == CONTROL_POINTS_NUM);
    
    Vector3 tangentStart = controlPoints.at(1) - controlPoints.at(0);
    Vector3 orthogonalStart = tangentStart.getTangentVector();

    Vector3 tangentEnd = controlPoints.at(2) + controlPoints.at(3);
    Vector3 orthogonalEnd = tangentEnd.getTangentVector();

    return false;
}

void Curve::split(std::vector<Vector3> &left, std::vector<Vector3> &right) const
{
    Vector3 a0 = (m_p0 + m_p1) / 2.0f;
    Vector3 a1 = (m_p1 + m_p2) / 2.0f;
    Vector3 a2 = (m_p2 + m_p3) / 2.0f; 

    Vector3 b0 = (a0 + a1) / 2.0f;
    Vector3 b1 = (a1 + a2) / 2.0f;

    Vector3 c0 = (b0 + b1) / 2.0f;

    //for clarity
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
