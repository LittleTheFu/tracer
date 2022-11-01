#include "frame.h"
#include <cassert>

Frame::Frame(const Vector3 &normal, const Vector3 &tangent)
{
    if(normal.isZero())
    {
        // assert("normal is zero!");
    }

    if(tangent.isZero())
    {
        // assert("tangent is zero!");
    }

    if(!normal.isPerpendicular(tangent))
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