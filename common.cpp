#include "common.h"
#include <cmath>
#include <limits>
#include <cstdlib>

const float Common::PI = 3.14159274101257324219f;
const float Common::TWO_PI = 2 * Common::PI;
const float Common::INV_PI = 1 / Common::PI;
const float Common::INV_TWO_PI = 1 / Common::TWO_PI;

const float Common::FLOAT_SAMLL_NUMBER = 0.1f;
const float Common::FLOAT_MAX = std::numeric_limits<float>::max();

const Vector3 Common::LOCAL_NORMAL = Vector3(0, 0, 1);
const Color Common::LIGHT_COLOR = Color::COLOR_WHITE;

const float Common::SAMPLE_LIGHTR_CORRECT_FACTOR = 0.96;

const bool Common::float_equal(float x, float y)
{
    float diff = std::abs(x - y);

    return diff < FLOAT_SAMLL_NUMBER;
}

const float Common::clamp(float v, float min, float max)
{
    if (v < min)
        return min;

    if (v > max)
        return max;

    return v;
}

const float Common::genRandomDecimal()
{
    const float max = (float)RAND_MAX;
    const float u = std::rand() / max;

    return u;
}
