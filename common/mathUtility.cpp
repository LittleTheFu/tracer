#include "mathUtility.h"
#include "mathConstantDef.h"
#include <algorithm>
#include <cmath>
#include <cassert>

bool MathUtility::is_in_range(float value, float low, float high, bool equalLow, bool equalHigh)
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

bool MathUtility::is_float_equal(float x, float y)
{
    float diff = std::abs(x - y);

    return diff < MathConstant::FLOAT_SAMLL_NUMBER;
}

bool MathUtility::is_float_zero(float x)
{
    return is_float_equal(x, MathConstant::FLOAT_SAMLL_NUMBER);
}

float MathUtility::clamp(float v, float min, float max)
{
    if (v < min)
        return min;

    if (v > max)
        return max;

    return v;
}

bool MathUtility::getOverlap(float t00, float t01, float t10, float t11, float &tMin, float &tMax)
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

float MathUtility::delta(float a, float b, float c)
{
    return b * b - 4 * a * c;
}

bool MathUtility::solveLinerEquation(float a, float b, float c, float &r_min, float &r_max)
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

float MathUtility::interpolate(float a, float b, float t)
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

float MathUtility::genRandomDecimal()
{
    const float max = (float)RAND_MAX;
    const float u = std::rand() / max;

    return u;
}

float MathUtility::genRamdomSignDecimal()
{
    float v = 2.0f * (genRandomDecimal() - 0.5f);

    return v;
}

float MathUtility::sampleExponential(float lambda)
{
  return -std::log(1.0f - genRandomDecimal()) / lambda;
}

int MathUtility::sampleFromWeights(std::initializer_list<float> weights)
{
    if(weights.size() == 0)
        assert(false);

    for(auto w : weights)
    {
        if(w <= 0)
            assert(false);
    }
    
    float totalWeight = 0.0f;
    for(auto w : weights)
    {
        totalWeight += w;
    }
    
    float r = genRandomDecimal() * totalWeight;
    float cumulateWeight = 0.0f;
    int index  = 0;
    for(auto it = weights.begin(); it != weights.end(); it++)
    {
        cumulateWeight += *it;
        if(r <= cumulateWeight)
        {
            index = std::distance(weights.begin(), it) - 1;
        }
    }

    return index;
}

int MathUtility::getMaxIndex(float a0, float a1, float a2)
{
    if (a0 >= a1 && a0 >= a2)
    {
        return 0;
    }
    else if (a1 >= a0 && a1 >= a2)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}