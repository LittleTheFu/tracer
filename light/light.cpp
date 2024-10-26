#include "light.h"
#include "ball.h"
#include "hitrecord.h"
#include "mathUtility.h"

Light::Light(const Vector3 &position, float r)
{
    m_pGeometry = new Ball(Vector3::ZERO, position, r, nullptr);
}

void Light::applyTransform(const Transform &t)
{
    m_pGeometry->applyTransform(t);
}

void Light::setTag(Tag tag)
{
    m_pGeometry->setTag(tag);
}

bool Light::hit(const Ray &ray, float &t, Vector3 &normal, float &dot) const
{
    HitRecord record;

    bool isHit = m_pGeometry->hit(ray, record);

    t = record.t;
    normal = record.normal;
    dot = MathUtility::clamp((-ray.dir) * normal, 0, 1);

    return isHit;
}

Vector3 Light::sample(const Vector3 &thatPoint, float &pdf) const
{
    return m_pGeometry->sampleFromPoint(thatPoint, pdf);
}

const Geometry *Light::getGeometry() const
{
    return m_pGeometry;
}