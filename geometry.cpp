#include "geometry.h"

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

Vector3 Geometry::sampleFromPoint(const Vector3 &thatPoint, float &pdf) const
{
    pdf = 1;
    
    return Vector3::ZERO;
}