#include "simpleTracer.h"
#include <cassert>
#include "config.h"

Color SimpleTracer::trace(const ObjectPool *pool,
                          Ray &ray,
                          int bounceNum,
                          const HitRecord &currentState) const
{
    if (bounceNum == 1)
    {
       return HandleLastBounce(pool, ray, currentState);
    }

    HitRecord record;
    if (!pool->hitScene(ray, record))
        return Color::COLOR_BLACK;

    Ray newRay(record.point, record.reflect);
    if (bounceNum == 2)
    {
        prepareSampleLight(pool, newRay, record);
    }

    Color inputColor = trace(pool, newRay, bounceNum - 1, record);

    if(bounceNum == 2)
        return inputColor;
    //fix later
    // assert(inputColor.isValid());
    assert(currentState.reflectPdf > 0);

    Color ccolor = currentState.f * inputColor * currentState.dot / currentState.reflectPdf;

    // if(ccolor.validOverflow(0.98f) != 0)
    // {
    //     std::cout << ccolor << std::endl;
    // }

    return ccolor;
}

Color SimpleTracer::HandleLastBounce(const ObjectPool *pool,
                                     const Ray &ray,
                                     const HitRecord &currentState) const
{
    //if sample from inside of a surface, 
    //then we shouldn't consider it as a success sample event
    if( currentState.dot == 0)
    {
        return Color::COLOR_BLACK;
    }
    
    Color lightColor = pool->getColorFromLight(ray);

    // is this line needed?
    lightColor = lightColor * currentState.dot;

    // Color retColor = lightColor * currentState.f;
    Color retColor = lightColor * currentState.f / currentState.reflectPdf;

    //warning: We'll look into the reason for the bug(maybe?) later.
    // retColor.clamp();

    return retColor;
}

void SimpleTracer::prepareSampleLight(const ObjectPool *pool,
                                      Ray &newRay,
                                      HitRecord &record) const
{
    if (record.isDelta)
        return;

    // Vector3 fakeP(100,100,250);
    // Vector3 lightSurfacePoint = pool->m_pLight->sample(fakeP, record.reflectPdf);
    Vector3 lightSurfacePoint = pool->m_pLight->sample(record.point, record.reflectPdf);
    // Vector3 lightSurfacePoint = pool->m_pLight->getSurfacePoint(record.point);
    // record.reflectPdf = 1;
    Vector3 lightDir = lightSurfacePoint - record.point;
    lightDir.normalize();

    record.reflect = lightDir;
    Vector3 lightNormal = pool->m_pLight->getNormal(lightSurfacePoint);
    record.dot = lightNormal * lightDir; // dot less than 0
    // record.dot = 1;
    if(record.dot < 0)
    {
        record.dot *= -1;
    }
    else
    {
        int f = 4;
    }

    newRay.dir = lightDir;
}