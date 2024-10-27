#ifndef _COMMON_H_
#define _COMMON_H_

#include "vector.h"
#include "color.h"
#include <string>

class Common
{
public:
    const static void printCurrentTime();

    const static Vector3 LOCAL_NORMAL;
    const static Color LIGHT_COLOR;

    const static float SAMPLE_LIGHTR_CORRECT_FACTOR;

    // for mist
    const static float SIGMA_T;
    const static float SIGMA_S;
};

#endif