#include "simpleTracer.h"
#include <cassert>

Color SimpleTracer::trace(const ObjectPool *pool, Ray &ray, int bounceNum, const HitRecord &currentState) const
{
    if (bounceNum == 1)
    {
       return HandleLastBounce(pool, ray, currentState);
    }

    HitRecord record;

    bool isLightHit = false;
    if (!pool->hitSceneWithLight(ray, record, isLightHit))
    {
        return Color::COLOR_BLACK;
    }

    if(isLightHit)
    {
        return Color::COLOR_WHITE * record.dotLight;
    }

    Ray newRay(record.point, record.reflect);
    if (bounceNum == 2)
    {
        prepareSampleLight(pool, newRay, record);
    }

    Color inputColor = trace(pool, newRay, bounceNum - 1, record);

    assert(currentState.reflectPdf > 0);
    Color ccolor = currentState.f * inputColor * currentState.dot / currentState.reflectPdf;

    return ccolor;
}

Color SimpleTracer::HandleLastBounce(const ObjectPool *pool, const Ray& ray, const HitRecord &currentState) const
{
    Color lightColor = pool->getColorFromLight(ray);

    // is this line needed?
    lightColor = lightColor * currentState.dot;

    Color retColor = lightColor * currentState.f / currentState.reflectPdf;

    return retColor;
}

void SimpleTracer::prepareSampleLight(const ObjectPool *pool, Ray &newRay, HitRecord &record) const
{
    if (record.isDelta)
        return;

    Vector3 lightSurfacePoint = pool->m_pLight->sample(record.point, record.reflectPdf);
    Vector3 lightDir = lightSurfacePoint - record.point;
    lightDir.normalize();

    record.reflect = lightDir;
    record.dot = record.normal * lightDir; // dot less than 0
    // record.dot = 1;

    newRay.dir = lightDir;
}