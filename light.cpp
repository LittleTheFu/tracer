#include "light.h"
#include "cball.h"
#include "hitrecord.h"
#include "common.h"

Light::Light(const Vector3 &position)
{
    m_pGeometry = new CBall(Vector3::ZERO, position, 5, nullptr);
}

void Light::setPosition(const Vector3 &position)
{
    if (m_pGeometry)
    {
        m_pGeometry->setPosition(position);
    }
}

Vector3 Light::getPosition() const
{
    return m_position;
}

bool Light::hit(const Ray &ray, float &t, Vector3 &normal, float &dot) const
{
    HitRecord record;

    bool isHit = m_pGeometry->hit(ray, record);

    t = record.t;
    normal = record.normal;
    dot = Common::clamp((-ray.dir) * normal, 0, 1);

    return isHit;
}