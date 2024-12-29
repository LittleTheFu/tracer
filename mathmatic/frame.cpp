#include <cassert>

#include "frame.h"

Frame::Frame(const Vector3 &normal, const Vector3 &tangent, const Vector3 &_origin)
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

    z_axis = normal;
    z_axis.normalize();

    x_axis = tangent;
    x_axis.normalize();

    y_axis = z_axis.cross(x_axis);
    y_axis.normalize();

    origin = _origin;
}

Frame::Frame(const Vector3 &normal, const Vector3 &_origin)
{
    Vector3 tangent = normal.getTangentVector();

    z_axis = normal;
    z_axis.normalize();

    x_axis = tangent;
    x_axis.normalize();

    y_axis = z_axis.cross(x_axis);
    y_axis.normalize();

    origin = _origin;
}

Vector3 Frame::pointToLocal(const Vector3 &point) const
{
    float xProj = (point - origin) * x_axis;
    float yProj = (point - origin) * y_axis;
    float zProj = (point - origin) * z_axis;

    return Vector3(xProj, yProj, zProj);
}

Vector3 Frame::pointToWorld(const Vector3 &point) const
{
    Vector3 resultX = point.x * x_axis;
    Vector3 resultY = point.y * y_axis;
    Vector3 resultZ = point.z * z_axis;
    
    return resultX + resultY + resultZ + origin;
}

Vector3 Frame::vectorToLocal(const Vector3 &vector) const
{
    float xProj = vector * x_axis;
    float yProj = vector * y_axis;
    float zProj = vector * z_axis;

    return Vector3(xProj, yProj, zProj);
}

Vector3 Frame::vectorToWorld(const Vector3 &vector) const
{
    Vector3 resultX = vector.x * x_axis;
    Vector3 resultY = vector.y * y_axis;
    Vector3 resultZ = vector.z * z_axis;

    return resultX + resultY + resultZ;
}
