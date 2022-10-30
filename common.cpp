#include "common.h"
#include <cmath>

const float Common::PI = 3.14159274101257324219f;
const float Common::TWO_PI = 2 * Common::PI;
const float Common::INV_PI = 1 / Common::PI;
const float Common::INV_TWO_PI = 1 / Common::TWO_PI;

const float Common::FLOAT_SAMLL_NUMBER = 0.0001f;
const Vector3 Common::LOCAL_NORMAL = Vector3(0, 0, 1);

const bool Common::float_equal(float x, float y)
{
    float diff = std::abs(x - y);

    return diff < FLOAT_SAMLL_NUMBER;
}

const float Common::getWeight(float rawWeight)
{
    if (rawWeight >= 0.2)
        return rawWeight;

    return 0.2;
    // if (rawWeight >= 1)
    //     return 1;

    // if (rawWeight >= 0.9)
    //     return 0.9;

    // if (rawWeight >= 0.8)
    //     return 0.8;

    // if (rawWeight >= 0.7)
    //     return 0.7;

    // if (rawWeight >= 0.6)
    //     return 0.6;

    // if (rawWeight >= 0.5)
    //     return 0.5;

    // if (rawWeight >= 0.4)
    //     return 0.4;

    // if (rawWeight >= 0.3)
    //     return 0.3;

    // return 0.2;
}
