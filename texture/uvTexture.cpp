#include "uvTexture.h"
#include "mathUtility.h"

Color UvTexture::getColor(float u, float v) const
{
    float uu = MathUtility::clamp(u, 0, 1);
    float vv = MathUtility::clamp(v, 0, 1);

    return Color(uu, 0, vv);
}