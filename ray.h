#ifndef _RAY_H_
#define _RAY_H_

#include "vector.h"

class ray {
    public:
        vector3 origin;
        vector3 dir;
        float t;
};

#endif