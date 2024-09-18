#ifndef _COMMON_H_
#define _COMMON_H_

#include "../vector.h"
#include "../color.h"
#include <string>

class Common
{
public:
    const static float PI;
    const static float TWO_PI;
    const static float INV_PI;
    const static float INV_TWO_PI;

    const static bool is_float_equal(float x, float y);
    const static bool is_float_zero(float x);
    const static float clamp(float v, float min, float max);

    //a*x*x + b*x + c = 0
    const static float delta(float a, float b, float c);
    const static bool solveLinerEquation(float a, float b, float c, float &r_min, float &r_max);

    const static float interpolate(float a, float b, float t);
    // const static float TrilinearInterpolation();

    const static float genRandomDecimal();
    const static float genRamdomSignDecimal();
    
    const static float FLOAT_SAMLL_NUMBER;
    const static float FLOAT_MAX;

    const static Vector3 LOCAL_NORMAL;
    const static Color LIGHT_COLOR;

    const static float SAMPLE_LIGHTR_CORRECT_FACTOR;

    const static std::string LENA;

    //for mist
    const static float SIGMA_T;
    const static float SIGMA_S;

    //tag
    const static int TAG_PLANE_LEFT;
    const static int TAG_PLANE_RIGHT;
    const static int TAG_PLANE_TOP;
    const static int TAG_PLANE_BOTTOM;
    const static int TAG_PLANE_FRONT;
    const static int TAG_PLANE_BACK;

    const static int TAG_LIGHT;

    const static unsigned int default_screen_width;
    const static unsigned int default_screen_height;
};

#endif
