#ifndef _MATH_UTILITY_H_
#define _MATH_UTILITY_H_

#include <initializer_list>
#include <complex>

class MathUtility
{
public:
    static bool is_in_range(float value, float low, float high, bool equalLow, bool equalHigh);

    static bool is_float_equal(float x, float y);
    static bool is_float_zero(float x);
    static float clamp(float v, float min, float max);

    static bool getOverlap(float t00, float t01, float t10, float t11, float &tMin, float &tMax);

    //a*x*x + b*x + c = 0
    static float delta(float a, float b, float c);
    static bool solveLinerEquation(float a, float b, float c, float &r_min, float &r_max);

    static float interpolate(float a, float b, float t);
    // const static float TrilinearInterpolation();

    static float genRandomDecimal();
    static float genRamdomSignDecimal();

    //sample e^(-lambda*t)
    static float sampleExponential(float lambda, float &pdf);
    static int sampleFromWeights(std::initializer_list<float> weights);

    static void sampleFromUnitDisk(float &x, float &y);

    static int getMaxIndex( float a0, float a1, float a2);

    static float smooth(float t);
    static float getSign(float x);

    //should be extract to a template function,later...
    static float sq(float x);
    static std::complex<float> sq_c(std::complex<float> x);
};

#endif