#ifndef _FRAME_H_
#define _FRAME_H_

#include "vector.h"

class Frame
{
public:
    Frame(const Vector3 &normal, const Vector3 &tangent, const Vector3 &_origin = Vector3::ZERO);

    Vector3 pointToLocal(const Vector3 &point) const;
    Vector3 pointToWorld(const Vector3 &point) const;

    Vector3 vectorToLocal(const Vector3 &vector) const;
    Vector3 vectorToWorld(const Vector3 &vector) const;

    //normal version needed?
    //normal to world?
    //normal to local?

    Vector3 x_axis;
    Vector3 y_axis;
    Vector3 z_axis;

    Vector3 origin;
};

#endif