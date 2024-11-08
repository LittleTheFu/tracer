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

Vector3 Light::getSurfacePoint(const Vector3 &thatPoint) const
{
    Ball *pBall = (Ball*)m_pGeometry;
    Vector3 center = pBall->getPosition();
    Vector3 dir = thatPoint - center;
    dir.normalize();
    dir *= pBall->r;

    return center + dir;
}

Vector3 Light::getNormal(const Vector3 point) const
{
    Vector3 center = m_pGeometry->getTransform().transformPoint(Vector3::ZERO);
    Vector3 normal = point - center;
    normal.normalize();

    return normal;
}

const Geometry *Light::getGeometry() const
{
    return m_pGeometry;
}