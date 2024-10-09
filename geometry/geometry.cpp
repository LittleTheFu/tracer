#include "geometry.h"

Geometry::Geometry()
{
    m_pMtrl = nullptr;
}

void Geometry::init(const Vector3 &rotate, const Vector3 &position)
{
    // m_transform.rotate(rotate);
    // m_transform.translate(position);
    m_transform.set(rotate, position);
}

void Geometry::setPosition(const Vector3 &position)
{
    m_transform.translate(position);
}

void Geometry::setTag(int tag)
{
    m_tag = tag;
}

int Geometry::getTag() const
{
    return m_tag;
}

void Geometry::applyTransform(const Transform &t)
{
    m_transform.applyTransform(t);
}

void Geometry::setTransform(const Transform &t)
{
    m_transform = t;
}

Transform Geometry::getTransform() const
{
    return m_transform;
}

void Geometry::setMaterial(const Material *pMtrl)
{
    m_pMtrl = pMtrl;
}

Vector3 Geometry::sampleFromPoint(const Vector3 &thatPoint, float &pdf) const
{
    pdf = 1;

    return Vector3::ZERO;
}

Color Geometry::get_f(const Vector3 &wo, const Vector3 &wi, const Vector3 &point, const Vector3 &normal) const
{
    //transform to local frame is needed

    // if(m_pMtrl)
    // {
    //     return m_pMtrl->get_f(wo, wi);
    // }

    return Color::COLOR_WHITE;
}

float Geometry::surfaceArea() const
{
    return 0.0f;
}

void Geometry::buildBoundBox() const
{
}

BoundBox Geometry::getBoundBox()
{
    return m_boundBox;
}
