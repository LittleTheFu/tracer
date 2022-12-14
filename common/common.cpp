#include "common.h"
#include <cmath>
#include <limits>
#include <cstdlib>

const float Common::PI = 3.14159274101257324219f;
const float Common::TWO_PI = 2 * Common::PI;
const float Common::INV_PI = 1 / Common::PI;
const float Common::INV_TWO_PI = 1 / Common::TWO_PI;

const float Common::FLOAT_SAMLL_NUMBER = 0.0001f;
const float Common::FLOAT_MAX = std::numeric_limits<float>::max();

const Vector3 Common::LOCAL_NORMAL = Vector3(0, 0, 1);
const Color Common::LIGHT_COLOR = Color::COLOR_WHITE;

const float Common::SAMPLE_LIGHTR_CORRECT_FACTOR = 0.96;

const float Common::SIGMA_T = 0.1;
const float Common::SIGMA_S = 0.2;

const std::string Common::LENA = "resource/lena.png";

const int Common::TAG_PLANE_LEFT = 1;
const int Common::TAG_PLANE_RIGHT = 2;
const int Common::TAG_PLANE_TOP = 3;
const int Common::TAG_PLANE_BOTTOM = 4;
const int Common::TAG_PLANE_FRONT = 5;
const int Common::TAG_PLANE_BACK = 6;

const int Common::TAG_LIGHT = 1001;

const bool Common::is_float_equal(float x, float y)
{
    float diff = std::abs(x - y);

    return diff < FLOAT_SAMLL_NUMBER;
}

const bool Common::is_float_zero(float x)
{
    return is_float_equal(x, FLOAT_SAMLL_NUMBER);
}

const float Common::clamp(float v, float min, float max)
{
    if (v < min)
        return min;

    if (v > max)
        return max;

    return v;
}

const float Common::interpolate(float a, float b, float t)
{
    if (t <= 0)
    {
        return a;
    }

    if (t >= 1)
    {
        return b;
    }

    return a * (1 - t) + b * t;
}

const float Common::genRandomDecimal()
{
    const float max = (float)RAND_MAX;
    const float u = std::rand() / max;

    return u;
}

const float Common::genRamdomSignDecimal()
{
    float v = 2 * (genRandomDecimal() - 0.5);

    return v;
}
