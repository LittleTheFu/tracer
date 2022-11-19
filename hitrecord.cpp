#include "hitrecord.h"
#include "common/common.h"

HitRecord::HitRecord()
{
    t0 = Common::FLOAT_MAX;
    t1 = Common::FLOAT_MAX;

    isMirror = false;
    isMistHit = false;
}