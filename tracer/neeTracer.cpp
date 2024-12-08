#include "neeTracer.h"
#include "hitrecord.h"
#include "mathUtility.h"


NeeTracer::NeeTracer(int depth)
{
    if(depth > 1)
        m_depth = depth;
}

Color NeeTracer::trace(std::shared_ptr<const ObjectPool> pool, Ray &ray) const
{
    // Color color = Color::COLOR_BLACK;
    Color color = traceFirstBounce(pool, ray);
    Color beta = Color::COLOR_WHITE;

    int depth = 0;
    Ray hitRay(ray);
    while (true)
    {
        if (depth > m_depth)
            break;

        depth++;

        HitRecord record;
        if (!pool->hitScene(hitRay, record))
        {
            color += Color::COLOR_BLACK;
            break;
        }

        //sample light
        if(record.isDelta)
        {
            Ray deltaLightRay(record.point, record.reflect);
            Color lightColor = pool->getColorFromLight(deltaLightRay);
            color += beta * lightColor;
        }
        else
        {
            float sampleLightPdf;
            Vector3 lightSurfacePoint = pool->m_pLight->sample(record.point, sampleLightPdf);

            Vector3 lightDir = lightSurfacePoint - record.point;
            lightDir.normalize();

            //plus lightDir * 0.001f is a hotfix to avoid self intersection
            Ray sampleLightRay(record.point + lightDir * 0.001f, lightDir);
            Color lightColor = pool->getColorFromLight(sampleLightRay);
          
            //to be fixed later : test visibility with light first?
            float absDot = std::abs(record.normal * lightDir);
            color += beta * lightColor * record.f * (absDot / sampleLightPdf);
            //warning: record.f above should be recaculated
            //to be fixed later
        }

        //after sampling light
        // record.dot has been setted to 1 if it is delta
        // if(!record.isDelta)
        beta *= (record.f * record.dot);

        //trace new ray
        // multiply by a 0.001f is a lazy way to avoid self intersection
        float sign = MathUtility::getSign(record.normal * record.reflect);
        hitRay.origin = record.point + sign * record.normal * 0.001f;
        hitRay.dir = record.reflect;
    }

    return color;
}
