#include "randomTracer.h"
#include <cassert>

Color RandomTracer::trace(const ObjectPool *pool,
                          const BVH *bvh,
                          Ray &ray,
                          int bounceNum,
                          const HitRecord &currentState) const
{
    HitRecord record;

    if (bounceNum == 1)
    {
        Color lightColor = pool->getColorFromLight(ray);
        lightColor = lightColor * currentState.f / currentState.reflectPdf;
        return lightColor;
    }

    bool hit = false;
    bool isLightHit = false;

    hit = pool->hitSceneWithLight(ray, record, isLightHit);

    if (!hit)
        return Color::COLOR_BLACK;
    if (isLightHit)
        return Color::COLOR_WHITE;

    Ray newRay(record.point, record.reflect);

    Color inputColor = trace(pool, bvh, newRay, bounceNum - 1, record);

    assert(currentState.reflectPdf > 0);
    Color ccolor = currentState.f * inputColor * currentState.dot / currentState.reflectPdf;

    return ccolor;
}