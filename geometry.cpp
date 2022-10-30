#include "geometry.h"

void Geometry::init(const Vector3 &rotate, const Vector3 &position)
{
    m_transform.rotate(rotate);
    m_transform.translate(position);
}