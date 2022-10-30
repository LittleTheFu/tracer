#ifndef _COMMON_H_
#define _COMMON_H_

#include "vector.h"

class Common
{
public:
    const static float PI;
    const static float TWO_PI;
    const static float INV_PI;
    const static float INV_TWO_PI;

    const static float getWeight(float rawWeight);
    const static bool float_equal(float x, float y);

    const static float FLOAT_SAMLL_NUMBER;
    const static float FLOAT_MAX;

    const static Vector3 LOCAL_NORMAL;
};

#endif
