#include "simpleTracer.h"
#include <cassert>

Color SimpleTracer::trace(const ObjectPool *pool, Ray &ray, int bounceNum, const HitRecord &currentState) const
{
    if (bounceNum == 1)
    {
        // does this ray can hit the light?
        // return light * cos * cos * sample_f / pdf

        Color lightColor = pool->getColorFromLight(ray);

        // is this line needed?
        lightColor = lightColor * currentState.dot;

        Color retColor = lightColor * currentState.f / currentState.reflectPdf;

        return retColor;
        // return lightColor;
    }

    HitRecord record;

    if (!pool->hitScene(ray, record))
    {
        return Color::COLOR_BLACK;
    }
    // }

    Ray newRay(record.point, record.reflect);
    if (bounceNum == 2)
    {
        Vector3 lightSurfacePoint = pool->m_pLight->sample(record.point, record.reflectPdf);
        Vector3 lightDir = lightSurfacePoint - record.point;
        lightDir.normalize();

        record.reflect = lightDir;
        record.dot = record.normal * lightDir; // dot less than 0
        // record.dot = 1;

        newRay.dir = lightDir;
    }

    Color inputColor = trace(pool, newRay, bounceNum - 1, record);

    assert(currentState.reflectPdf > 0);
    Color ccolor = currentState.f * inputColor * currentState.dot / currentState.reflectPdf;

    return ccolor;
}