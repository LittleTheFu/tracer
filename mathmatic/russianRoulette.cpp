#include "russianRoulette.h"
#include "mathUtility.h"

bool RussianRoulette::evaluate(float p) const
{
    return MathUtility::genRandomDecimal() < p;
}