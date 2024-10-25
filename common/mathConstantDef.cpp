#include "mathConstantDef.h"
#include <limits>

const float MathConstant::PI = 3.14159274101257324219f;
const float MathConstant::TWO_PI = 2 * MathConstant::PI;
const float MathConstant::FOUR_PI = 4 * MathConstant::PI;
const float MathConstant::INV_PI = 1 / MathConstant::PI;
const float MathConstant::INV_TWO_PI = 1 / MathConstant::TWO_PI;

const float MathConstant::FLOAT_SAMLL_NUMBER = 0.0001f;
const float MathConstant::FLOAT_MAX = std::numeric_limits<float>::max();
const float MathConstant::FLOAT_POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
const float MathConstant::FLOAT_NEGETIVE_INFINITY = -std::numeric_limits<float>::infinity();