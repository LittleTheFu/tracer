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

    z_axis = normal;
    z_axis.normalize();

    x_axis = tangent;
    x_axis.normalize();

    y_axis = z_axis.cross(x_axis);
    y_axis.normalize();
}

Vector3 Frame::toLocal(const Vector3 &point) const
{
    float xProj = point * x_axis;
    float yProj = point * y_axis;
    float zProj = point * z_axis;

    return Vector3(xProj, yProj, zProj);
}

Vector3 Frame::toWorld(const Vector3 &point) const
{
    Vector3 resultX = point.x * x_axis;
    Vector3 resultY = point.y * y_axis;
    Vector3 resultZ = point.z * z_axis;
    
    return resultX + resultY + resultZ;
}