#include "tracer.h"

Color Tracer::trace(std::shared_ptr<const ObjectPool> pool,
                    Ray &ray,
                    int bounceNum,
                    const HitRecord &currentState) const
{
    return Color::COLOR_RED;
}

Color Tracer::trace(std::shared_ptr<const ObjectPool> pool, Ray &ray) const
{
    return Color::COLOR_RED;
}

Color Tracer::traceFirstBounce(std::shared_ptr<const ObjectPool> pool, Ray &ray) const
{
    if(!pool)
        return Color::COLOR_BLACK;

    Color lightColor = pool->getColorFromLight(ray);
    return lightColor;
}
