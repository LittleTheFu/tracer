#include "mathUtility.h"
#include "mathConstantDef.h"
#include <algorithm>
#include <cmath>

const bool MathUtility::is_in_range(float value, float low, float high, bool equalLow, bool equalHigh)
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

const bool MathUtility::is_float_equal(float x, float y)
{
    float diff = std::abs(x - y);

    return diff < MathConstant::FLOAT_SAMLL_NUMBER;
}

const bool MathUtility::is_float_zero(float x)
{
    return is_float_equal(x, MathConstant::FLOAT_SAMLL_NUMBER);
}

const float MathUtility::clamp(float v, float min, float max)
{
    if (v < min)
        return min;

    if (v > max)
        return max;

    return v;
}

const bool MathUtility::getOverlap(float t00, float t01, float t10, float t11, float &tMin, float &tMax)
{
    float t0_min = t00;
    float t0_max = t01;
    float t1_min = t10;
    float t1_max = t11;
    
    if(t0_min > t0_max)
        std::swap(t0_min, t0_max);

    if(t1_min > t1_max)
        std::swap(t1_min, t1_max);

    //swap the two lines to keep t0_min is the smaller min
    if(t0_min > t1_min)
    {
        std::swap(t0_min, t1_min);
        std::swap(t0_max, t1_max);
    }

    if(t0_max < t1_min)
        return false;
    
    tMin = t1_min;
    tMax = std::min(t0_max, t1_max);

    return true;
}

const float MathUtility::delta(float a, float b, float c)
{
    return b * b - 4 * a * c;
}

const bool MathUtility::solveLinerEquation(float a, float b, float c, float &r_min, float &r_max)
{
    // check a == 0(not done)

    const float delta = MathUtility::delta(a, b, c);
    if (delta < 0.0f)
        return false;

    r_min = (-b + std::sqrt(delta)) / (2 * a);
    r_max = (-b - std::sqrt(delta)) / (2 * a);

    if (r_min > r_max)
    {
        std::swap(r_min, r_max);
    }

    return true;
}

const float MathUtility::interpolate(float a, float b, float t)
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

const float MathUtility::genRandomDecimal()
{
    const float max = (float)RAND_MAX;
    const float u = std::rand() / max;

    return u;
}

const float MathUtility::genRamdomSignDecimal()
{
    float v = 2.0f * (genRandomDecimal() - 0.5f);

    return v;
}