#include "hitrecord.h"
#include "mathConstantDef.h"

HitRecord::HitRecord()
{
    t0 = MathConstant::FLOAT_MAX;
    t1 = MathConstant::FLOAT_MAX;

    t = MathConstant::FLOAT_MAX;

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

Media HitRecord::getMeida(const Vector3 &dir) const
{
    float dot = normal * dir;
    if (dot >= 0)
        return outsideMedia;

    return insideMedia;
}
