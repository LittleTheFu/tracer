#include "curve.h"

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
    if (depth <= 0)
        return false;

    return hitRecursive(ray, record, depth - 1, t0, t1);
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
