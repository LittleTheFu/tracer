#include "uvTexture.h"
#include "common/common.h"

Color UvTexture::getColor(float u, float v) const
{
    float uu = Common::clamp(u, 0, 1);
    float vv = Common::clamp(v, 0, 1);

    return Color(uu, 0, vv);
}