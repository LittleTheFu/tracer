#include "hitrecord.h"
#include "common/common.h"

HitRecord::HitRecord()
{
    t0 = Common::FLOAT_MAX;
    t1 = Common::FLOAT_MAX;

    isMirror = false;
    isMistHit = false;

    tag = -1;
}

bool HitRecord::isPointValid() const
{
    if(point.x < -100)
    {
        return false;
    }

    if(point.x > 100)
    {
        return false;
    }

    if(point.y < -100)
    {
        return false;
    }

    if(point.y > 100)
    {
        return false;
    }

    return true;
}