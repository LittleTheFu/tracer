#include "tracer.h"

Color Tracer::trace(const ObjectPool *pool,
                    Ray &ray,
                    int bounceNum,
                    const HitRecord &currentState) const
{
    return Color::COLOR_AQUA;
}

Color Tracer::traceFirstBounce(const ObjectPool *pool, Ray &ray) const
{
    if(!pool)
        return Color::COLOR_BLACK;

    Color lightColor = pool->getColorFromLight(ray);
    return lightColor;
}
