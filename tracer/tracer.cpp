#include "tracer.h"

Color Tracer::trace(const ObjectPool *pool,
                    const BVH *bvh,
                    Ray &ray,
                    int bounceNum,
                    const HitRecord &currentState) const
{
    return Color::COLOR_AQUA;
}