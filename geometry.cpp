#include "geometry.h"

void Geometry::init(const Vector3 &rotate, const Vector3 &position)
{
    m_transform.rotate(rotate);
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