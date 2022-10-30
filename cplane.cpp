#include "cplane.h"

bool CPlane::hit(const Ray &ray, HitRecord &record) const
{
    return false;
}

Vector3 CPlane::dpdu(const Vector3 &point) const
{
    return Vector3(1, 0, 0);
}

Vector3 CPlane::dpdv(const Vector3 &point) const
{
    return Vector3(0, 1, 0);
}