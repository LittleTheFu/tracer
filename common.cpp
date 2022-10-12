#include "common.h"

const float Common::PI = 3.14159274101257324219f;
const float Common::FLOAT_SAMLL_NUMBER = 0.0001f;

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
