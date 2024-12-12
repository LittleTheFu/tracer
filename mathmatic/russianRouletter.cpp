#include "russianRouletter.h"
#include "mathUtility.h"

bool RussianRouletter::evaluate(float p) const
{
    return MathUtility::genRandomDecimal() < p;
}