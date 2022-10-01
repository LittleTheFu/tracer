#include "ray.h"
#include <limits>
#include <cmath>

Ray::Ray(const Vector3 &origin, const Vector3 &dir)
{
    this->origin = origin;
    this->dir = dir;
    this->dir.normalize();
}

bool Ray::localHit(const Ball &ball, float &t, Vector3 &point, Vector3 &normal, Vector3 &randomReflectVector) const
{
    t = std::numeric_limits<float>::max();

    const Ray newRay = genNewRay(ball.transform);

    // page 135 57
    const float a = newRay.dir.lenthSqr();
    const float b = 2 * (newRay.dir * newRay.origin - newRay.dir * ball.getLocalCenter());
    const float c = (newRay.origin - ball.getLocalCenter()).lenthSqr() - ball.r * ball.r;

    const float delta = b * b - 4 * a * c;

    if (delta <= 0.0f)
        return false;

    float t0 = (-b + sqrt(delta)) / (2 * a);
    float t1 = (-b - sqrt(delta)) / (2 * a);
    float temp = 0;
    if (t0 > t1)
    {
        temp = t0;
        t0 = t1;
        t1 = temp;
    }

    bool hit = t0 > 0.0f;
    t = t0;

    if (!hit)
    {
        if (t1 > 0.0f)
        {
            hit = true;
            t = t1;
        }
    }

    if (hit)
    {
        const Vector3 localPoint = newRay.origin + t * newRay.dir;
        point = ball.transform.transformPoint(localPoint);

        const Vector3 localNormal = ball.getLocalNormal(localPoint);
        normal = ball.transform.transformNormal(localNormal);
        // normal = ball.transform.transformVector(localNormal);

        const Vector3 dpdu = ball.dpdu(localPoint);
        const Vector3 dpdv = ball.dpdv(localPoint);

        Vector3 r = Vector3::getRandomVector();
        // float rx = r * dpdu;
        // float ry = r * dpdv;
        // float rz = r * localNormal;
        if (r.z == 0)
            r.z = 1;
        if (r.z < 0)
            r.z *= -1;

        Vector3 localReflectVector = r.x * dpdu + r.y * dpdv + r.z * localNormal;
        localReflectVector.normalize();
        randomReflectVector = ball.transform.transformVector(localReflectVector);

        if (ball.mtrl.specular)
        {
            randomReflectVector = newRay.dir.reflect(localNormal);
        }
    }

    return hit;
}

bool Ray::localHit(const Plane &plane, float &t, Vector3 &point, Vector3 &normal, Vector3 &randomReflectVector) const
{
    t = std::numeric_limits<float>::max();

    const Ray newRay = genNewRay(plane.transform);

    if (newRay.dir * plane.getLocalNormal() >= 0)
    {
        return false;
    }

    const float n = (plane.getLocalCenter() - newRay.origin) * plane.getLocalNormal();
    const float d = newRay.dir * plane.getLocalNormal();

    t = n / d;

    Vector3 localPoint = newRay.origin + t * newRay.dir;

    if (!plane.isLocalIn(localPoint))
    {
        return false;
    }

    point = plane.transform.transformPoint(localPoint);
    normal = plane.transform.transformVector(plane.getLocalNormal());

    const Vector3 localReflectVector = Vector3::getRandomVector();
    randomReflectVector = plane.transform.transformVector(localReflectVector);
    // randomReflectVector = plane.transform.transformVector(plane.getLocalNormal());

    return true;
}

bool Ray::hit(const Ball &ball, float &t, Vector3 &point) const
{
    t = std::numeric_limits<float>::max();

    // page 135 57
    const float a = dir.lenthSqr();
    const float b = 2 * (dir * origin - dir * ball.getCenter());
    // const float c = origin.lenthSqr() +
    //                 ball.getCenter().lenthSqr() -
    //                 2 * (origin * ball.getCenter()) -
    //                 ball.r * ball.r;
    const float c = (origin - ball.getCenter()).lenthSqr() - ball.r * ball.r;

    const float delta = b * b - 4 * a * c;

    if (delta <= 0.0f)
        return false;

    float t0 = (-b + sqrt(delta)) / (2 * a);
    float t1 = (-b - sqrt(delta)) / (2 * a);
    float temp = 0;
    if (t0 > t1)
    {
        temp = t0;
        t0 = t1;
        t1 = temp;
    }

    bool hit = t0 > 0.0f;
    t = t0;

    if (!hit)
    {
        if (t1 > 0.0f)
        {
            hit = true;
            t = t1;
        }
    }

    if (hit)
    {
        point = origin + t * dir;
    }

    return hit;
}

bool Ray::hit(const Plane &plane, float &t, Vector3 &point) const
{
    t = std::numeric_limits<float>::max();

    if (dir * plane.normal >= 0)
    {
        return false;
    }

    const float n = (plane.center - origin) * plane.normal;
    const float d = dir * plane.normal;

    t = n / d;

    point = origin + t * dir;

    if (!plane.isIn(point))
    {
        return false;
    }

    return true;
}

Ray Ray::genNewRay(const Transform &transform) const
{
    const Vector3 o = transform.invTransformPoint(origin);
    const Vector3 d = transform.invTransformVector(dir);

    return Ray(o, d);
}

float Ray::getDistranceT(const Vector3 &that) const
{
    return 0;
}

float Ray::getT(const Ray &ray, const Vector3 &thatPoint)
{
    Vector3 d = thatPoint - ray.origin;
    if (ray.dir.x > ray.dir.y)
    {
        if (ray.dir.x > ray.dir.z)
        {
            return d.x / ray.dir.x;
        }
        else
        {
            return d.z / ray.dir.z;
        }
    }
    else
    {
        if (ray.dir.y > ray.dir.z)
        {
            return d.y / ray.dir.y;
        }
        else
        {
            return d.z / ray.dir.z;
        }
    }

    return 0;
}