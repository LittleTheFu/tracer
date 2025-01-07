#include "geometry.h"

Geometry::Geometry()
{
    m_pMtrl = nullptr;

    m_insideMedia.set(1,1,1,Color::COLOR_WHITE);
}

void Geometry::init(const Vector3 &rotate, const Vector3 &position)
{
    m_transform.set(rotate, position);
}

void Geometry::setPosition(const Vector3 &position)
{
    m_transform.translate(position);
}

Vector3 Geometry::getPosition() const
{
    Vector3 p = m_transform.transformPoint(Vector3::ZERO);
    return p;
}

Vector3 Geometry::getLocalPosition(const Vector3 &worldPosition) const
{
    return m_transform.invTransformPoint(worldPosition);
}

void Geometry::setTag(Tag tag)
{
    m_tag = tag;
}

Tag Geometry::getTag() const
{
    return m_tag;
}

std::string Geometry::getClassName() const
{
    return typeid(*this).name();
}

bool Geometry::testHit(const Ray &localRay, float &t) const
{
    return false;
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

void Geometry::setMaterial(std::shared_ptr<Material> pMtrl)
{
    m_pMtrl = pMtrl;
}

bool Geometry::isVolume() const
{
   return m_pMtrl == nullptr;
}

Vector3 Geometry::sampleFromPoint(const Vector3 &thatPoint, float &pdf) const
{
    pdf = 1;

    return Vector3::ZERO;
}

Vector3 Geometry::getCentroid() const
{
    return Vector3::ZERO;
}

float Geometry::surfaceArea() const
{
    return 0.0f;
}

void Geometry::buildBoundBox()
{
}

BoundBox Geometry::getBoundBox() const
{
    return m_boundBox;
}
