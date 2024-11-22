#include "volTracer.h"
Color VolTracer::trace(const ObjectPool *pool, Ray &ray, int bounceNum, const HitRecord &currentState) const
{
    return Color::COLOR_NAVY;
}

Color VolTracer::traceFirstBounce(const ObjectPool *pool, Ray &ray) const
{
    return Color::COLOR_NAVY;
}
