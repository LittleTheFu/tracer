#ifndef _MATH_UTILITY_H_
#define _MATH_UTILITY_H_

class MathUtility
{
public:
    const static bool is_in_range(float value, float low, float high, bool equalLow, bool equalHigh);

    const static bool is_float_equal(float x, float y);
    const static bool is_float_zero(float x);
    const static float clamp(float v, float min, float max);

    const static bool getOverlap(float t00, float t01, float t10, float t11, float &tMin, float &tMax);

    //a*x*x + b*x + c = 0
    const static float delta(float a, float b, float c);
    const static bool solveLinerEquation(float a, float b, float c, float &r_min, float &r_max);

    const static float interpolate(float a, float b, float t);
    // const static float TrilinearInterpolation();

    const static float genRandomDecimal();
    const static float genRamdomSignDecimal();

};

#endif