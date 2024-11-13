#include "randomTracer.h"
#include <cassert>

Color RandomTracer::trace(const ObjectPool *pool,
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

    hit = pool->hitScene(ray, record);

    if (!hit)
        return Color::COLOR_BLACK;

    Ray newRay(record.point, record.reflect);

    Color inputColor = trace(pool, newRay, bounceNum - 1, record);
    if(bounceNum == 2)
        return inputColor;

    assert(currentState.reflectPdf > 0);
    Color ccolor = currentState.f * inputColor * currentState.dot / currentState.reflectPdf;

    return ccolor;
}