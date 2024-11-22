#include "volTracer.h"
#include "mathUtility.h"
Color VolTracer::trace(const ObjectPool *pool, Ray &ray, int bounceNum, const HitRecord &currentState) const
{
    HitRecord record;
    bool isHit = pool->hitScene(ray, record);
    float tMax = record.t;
    
    float t = MathUtility::sampleExponential(ray.media.sigma_major);
    while(t < tMax)
    {
        float sigma_a = ray.media.sigma_a;
        float sigma_s = ray.media.sigma_s;
        float sigma_n = ray.media.sigma_n;

        int index = MathUtility::sampleFromWeights({sigma_a, sigma_s, sigma_n});

        if(index == 0)
        {
            //asborsption
            return ray.media.emitColor;
        }
        else if(index == 1)
        {
            if(bounceNum == 1)
                break;
            //scattering
            Vector3 dir = Vector3::sampleUniformFromSphere();
            Ray newRay(ray.getPosition(t), dir);
            return trace(pool, newRay, bounceNum - 1, record);
        }
        else
        {
            t += MathUtility::sampleExponential(ray.media.sigma_major);
        }
    }

    return Color::COLOR_NAVY;
}

Color VolTracer::traceFirstBounce(const ObjectPool *pool, Ray &ray) const
{
    return Color::COLOR_BLACK;
}
