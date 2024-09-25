#include "frame.h"
#include <cassert>

Frame::Frame(const Vector3 &normal, const Vector3 &tangent)
{
    if (normal.isZero())
    {
        // assert("normal is zero!");
    }

    if (tangent.isZero())
    {
        // assert("tangent is zero!");
    }

    if (!normal.isPerpendicular(tangent))
    {
        // assert("not Perpendicular!");
    }

    z = normal;
    z.normalize();

    x = tangent;
    x.normalize();

    y = z.cross(x);
    y.normalize();
}

Vector3 Frame::toLocal(const Vector3 &point) const
{
    float xProj = point * x;
    float yProj = point * y;
    float zProj = point * z;

    return Vector3(xProj, yProj, zProj);
}

Vector3 Frame::toWorld(const Vector3 &point) const
{
    Vector3 resultX = point.x * x;
    Vector3 resultY = point.y * y;
    Vector3 resultZ = point.z * z;
    
    return resultX + resultY + resultZ;
}