#include "light.h"
#include "cball.h"
#include "hitrecord.h"

Light::Light()
{
    m_pGeometry = new CBall(Vector3::ZERO, Vector3(5, 2, 30), 3, nullptr);
}

bool Light::hit(const Ray &ray, float &t, Vector3 &normal)
{
    HitRecord record;
    
    bool isHit = m_pGeometry->hit(ray, record);

    t = record.t;
    normal = record.normal;

    return isHit;
}