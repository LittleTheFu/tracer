#ifndef _FRAME_H_
#define _FRAME_H_

#include "vector.h"

class Frame
{
public:
    Frame(const Vector3 &normal, const Vector3 &tangent);

    Vector3 toLocal(const Vector3 &point) const;
    Vector3 toWorld(const Vector3 &point) const;

    Vector3 x_axis;
    Vector3 y_axis;
    Vector3 z_axis;
};

#endif