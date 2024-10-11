#include "simpleTracer.h"
#include <cassert>

#define _USE_POOL_ (1)

Color SimpleTracer::trace(const ObjectPool *pool,
                          const BVH *bvh,
                          Ray &ray,
                          int bounceNum,
                          const HitRecord &currentState) const
{
    if (bounceNum == 1)
    {
       return HandleLastBounce(pool, bvh, ray, currentState);
    }

    HitRecord record;

    bool isLightHit = false;
#if(_USE_POOL_)
    if (!pool->hitSceneWithLight(ray, record, isLightHit))
#else
    if (!bvh->hitSceneWithLight(ray, record, isLightHit))
#endif()
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
        prepareSampleLight(pool, bvh, newRay, record);
    }

    if(record.f != Color::COLOR_BLACK)
    {
        int a = 3;
    }

    Color inputColor = trace(pool, bvh, newRay, bounceNum - 1, record);
    assert(inputColor.isValid());
    assert(currentState.reflectPdf > 0);

    Color ccolor = currentState.f * inputColor * currentState.dot / currentState.reflectPdf;

    return ccolor;
}

Color SimpleTracer::HandleLastBounce(const ObjectPool *pool,
                                     const BVH *bvh,
                                     const Ray &ray,
                                     const HitRecord &currentState) const
{
    //if sample from inside of a surface, 
    //then we shouldn't consider it as a success sample event
    if( currentState.dot == 0)
    {
        return Color::COLOR_BLACK;
    }
    
#if(_USE_POOL_)
    Color lightColor = pool->getColorFromLight(ray);
#else
    Color lightColor = bvh->getColorFromLight(ray);
#endif()

    // is this line needed?
    lightColor = lightColor * currentState.dot;

    Color retColor = lightColor * currentState.f / currentState.reflectPdf;

    //warning: We'll look into the reason for the bug(maybe?) later.
    retColor.clamp();

    return retColor;
}

void SimpleTracer::prepareSampleLight(const ObjectPool *pool,
                                      const BVH *bvh,
                                      Ray &newRay,
                                      HitRecord &record) const
{
    if (record.isDelta)
        return;

#if(_USE_POOL_)
    Vector3 lightSurfacePoint = pool->m_pLight->sample(record.point, record.reflectPdf);
#else
    Vector3 lightSurfacePoint = bvh->m_pLight->sample(record.point, record.reflectPdf);
#endif()
    Vector3 lightDir = lightSurfacePoint - record.point;
    lightDir.normalize();

    record.reflect = lightDir;
    record.dot = record.normal * lightDir; // dot less than 0
    // record.dot = 1;
    if(record.dot < 0)
    {
        record.dot = 0;
    }

    newRay.dir = lightDir;
}