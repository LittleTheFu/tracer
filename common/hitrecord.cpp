#include "hitrecord.h"
#include "common.h"

HitRecord::HitRecord()
{
    t0 = Common::FLOAT_MAX;
    t1 = Common::FLOAT_MAX;

    t = Common::FLOAT_MAX;

    isMirror = false;
    isMistHit = false;

    isDelta = false;

    dotLight = 1;

    f = Color::COLOR_BLACK;
}

HitRecord HitRecord::getCloserOne(const HitRecord &that) const
{
    if (t < that.t)
        return *this;

    return HitRecord(that);
}
