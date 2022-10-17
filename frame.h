#ifndef _FRAME_H_
#define _FRAME_H_

#include "vector.h"

class Frame
{
public:
    Frame(const Vector3 &normal, const Vector3 &tangent);

    Vector3 x;
    Vector3 y;
    Vector3 z;
};

#endif