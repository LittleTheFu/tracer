#include "common.h"
#include <cmath>
#include <limits>
#include <cstdlib>
#include <chrono>

const float Common::PI = 3.14159274101257324219f;
const float Common::TWO_PI = 2 * Common::PI;
const float Common::FOUR_PI = 4 * Common::PI;
const float Common::INV_PI = 1 / Common::PI;
const float Common::INV_TWO_PI = 1 / Common::TWO_PI;

const float Common::FLOAT_SAMLL_NUMBER = 0.0001f;
const float Common::FLOAT_MAX = std::numeric_limits<float>::max();

const Vector3 Common::LOCAL_NORMAL = Vector3(0, 0, 1);
const Color Common::LIGHT_COLOR = Color::COLOR_WHITE;

const float Common::SAMPLE_LIGHTR_CORRECT_FACTOR = 0.96;

const float Common::SIGMA_T = 0.1;
const float Common::SIGMA_S = 0.2;

const std::string Common::LENA = "../resource/lena.png";
const std::string Common::BUNNY = "../resource/bunny.obj";
const std::string Common::SIMPLE_BUNNY = "../resource/simple_bunny.obj";
const std::string Common::LOW_BUNNY = "../resource/low_bunny.obj";
const std::string Common::LOW_LOW_BUNNY = "../resource/low_low_bunny.obj";

const int Common::TAG_PLANE_LEFT = 1;
const int Common::TAG_PLANE_RIGHT = 2;
const int Common::TAG_PLANE_TOP = 3;
const int Common::TAG_PLANE_BOTTOM = 4;
const int Common::TAG_PLANE_FRONT = 5;
const int Common::TAG_PLANE_BACK = 6;

const int Common::TAG_LIGHT = 1001;

const int Common::TAG_GLASS_BALL = 10001;
const int Common::TAG_MIRROR_BALL = 11001;

const  unsigned int Common::default_screen_width = 256;
const  unsigned int Common::default_screen_height = 256;

const bool Common::is_in_range(float value, float low, float high, bool equalLow, bool equalHigh)
{
    if(equalLow && equalHigh)
    {
        return value >= low && value <= high;
    }
    
    if(!equalLow && equalHigh)
    {
        return value > low && value <= high;
    }

    if(equalLow && !equalHigh)
    {
        return value >= low && value < high;
    }

    if(!equalLow && !equalHigh)
    {
        return value > low && value < high;
    }

    return false;
}

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

const float Common::delta(float a, float b, float c)
{
    return b * b - 4 * a * c;
}

const bool Common::solveLinerEquation(float a, float b, float c, float &r_min, float &r_max)
{
    // check a == 0(not done)

    const float delta = Common::delta(a, b, c);
    if (delta < 0.0f)
        return false;

    r_min = (-b + sqrt(delta)) / (2 * a);
    r_max = (-b - sqrt(delta)) / (2 * a);

    if (r_min > r_max)
    {
        std::swap(r_min, r_max);
    }

    return true;
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

const void Common::printCurrentTime()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // 转换为时间戳类型
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    // 转换为本地时间
    char *timeStr = std::ctime(&time);

    // 打印当前时间
    std::cout << "now is : " << timeStr << std::endl;
}
