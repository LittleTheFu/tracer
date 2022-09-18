#ifndef _RAY_H_
#define _RAY_H_

#include "vector.h"
#include "ball.h"

class Ray {
    public:
        Vector3 origin;
        Vector3 dir;
        float t;

        bool hit(const Ball& ball);
};

#endif