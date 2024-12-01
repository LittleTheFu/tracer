#ifndef _COMMON_H_
#define _COMMON_H_

#include "vector.h"
#include "color.h"

class Common
{
//for test bug
public:
    static Vector3 getNormal(const Vector3 &from, const Vector3 &to);

public:
    static void printCurrentTime();

    const static Vector3 LOCAL_NORMAL;
};

#endif