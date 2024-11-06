#ifndef _MATH_CONSTANT_DEF_H_
#define _MATH_CONSTANT_DEF_H_


#include "mathConstantDef.h"
#include <limits>

class MathConstant
{
public:
    inline const static float PI = 3.14159274101257324219f;
    inline const static float TWO_PI = 2 * PI;;
    inline const static float FOUR_PI = 4 * PI;
    inline const static float INV_PI = 1 / PI;
    inline const static float INV_TWO_PI = 1 / TWO_PI;

    inline const static float FLOAT_SAMLL_NUMBER = 0.0001f;
    inline const static float FLOAT_MAX = std::numeric_limits<float>::max();
    inline const static float FLOAT_POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
    inline const static float FLOAT_NEGETIVE_INFINITY = -std::numeric_limits<float>::infinity();
};

#endif