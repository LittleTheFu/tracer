#include "volTracer.h"
#include "mathUtility.h"
Color VolTracer::trace(const ObjectPool *pool, Ray &ray, int bounceNum, const HitRecord &currentState) const
{
    HitRecord record;
    bool isHit = pool->hitScene(ray, record);
    float tMax = record.t;
    
    float t;
    if(ray.media.sigma_major == 0.0f)
        t = tMax;
    else
        t = MathUtility::sampleExponential(ray.media.sigma_major);

    while(t < tMax)
    {
        float sigma_a = ray.media.sigma_a;
        float sigma_s = ray.media.sigma_s;
        float sigma_n = ray.media.sigma_n;

        Vector3 pt = ray.getPosition(t);
        Vector3 org(50,0,320);
        float lenSqr = (pt - org).lenthSqr();

        // if (ray.media.emitColor == Color::COLOR_NAVY)
        // {
        //     sigma_a = (12000 - lenSqr) / 12000;
        //     sigma_a *= sigma_a;
        //     // sigma_a = 1 - sigma_a;
        //     // if(sigma_a > 20)
        //     //     sigma_a = 20;

        //     int kkk = 333;

        //     if(sigma_a < 0.2)
        //     {
        //         kkk = 999;
        //     }

        //     if(sigma_a > 10)
        //     {
        //         kkk = 98;
        //     }
        // }

        // sigma_a = MathUtility::genRandomDecimal();
        // float xx = pt.x + 80;
        // sigma_a = xx / 500.0f;
        sigma_a = (m_noise.getValue(pt) + 1)/2.0f;
        sigma_a /= 20;
        if(sigma_a < 0)
            sigma_a = 0;

        int index = MathUtility::sampleFromWeights({sigma_a, sigma_s, sigma_n});

        if (index == 0)
        {
            return ray.media.emitColor;
        }
        else if(index == 1)
        {
            bounceNum--;
            if(bounceNum == 1)
                return Color::COLOR_BLACK;
                //  return ray.media.emitColor;
            //scattering
            Vector3 dir = Vector3::sampleUniformFromSphere();
            Ray newRay(ray.getPosition(t), dir);
            return trace(pool, newRay, bounceNum, record);
        }
        else
        {
            t += 2 * MathUtility::sampleExponential(ray.media.sigma_major);
        }
    }
        
    if (isHit)
    {
        Ray new_ray(ray.getPosition(tMax) + ray.dir * 0.01f, ray.dir);
        new_ray.media = record.getMeida(ray.dir);

        return trace(pool, new_ray, bounceNum, record);
    }
    
    return Color::COLOR_BLACK;
}

Color VolTracer::traceFirstBounce(const ObjectPool *pool, Ray &ray) const
{
    return Color::COLOR_BLACK;
}
