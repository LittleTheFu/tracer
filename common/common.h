#ifndef _COMMON_H_
#define _COMMON_H_

#include "vector.h"
#include "color.h"
#include <string>

class Common
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

    const static void printCurrentTime();

    const static Vector3 LOCAL_NORMAL;
    const static Color LIGHT_COLOR;

    const static float SAMPLE_LIGHTR_CORRECT_FACTOR;

    const static std::string LENA;
    const static std::string BUNNY;
    const static std::string SIMPLE_BUNNY;
    const static std::string LOW_BUNNY;
    const static std::string LOW_LOW_BUNNY;

    //for mist
    const static float SIGMA_T;
    const static float SIGMA_S;

    const static unsigned int default_screen_width;
    const static unsigned int default_screen_height;
};

#endif