#include "light.h"
#include "cball.h"
#include "hitrecord.h"
#include "common.h"

Light::Light()
{
    m_pGeometry = new CBall(Vector3::ZERO, Vector3(5, 2, 30), 3, nullptr);
}

bool Light::hit(const Ray &ray, float &t, Vector3 &normal, float &dot)
{
    HitRecord record;

    bool isHit = m_pGeometry->hit(ray, record);

    t = record.t;
    normal = record.normal;
    dot = Common::clamp((-ray.dir) * normal, 0, 1);

    return isHit;
}