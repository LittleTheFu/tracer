#include "neeTracer.h"
#include "hitrecord.h"
#include "mathUtility.h"

NeeTracer::NeeTracer(int depth)
{
    if (depth > 1)
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

        // sample light
        if (record.isDelta)
        {
            color += beta * sampleLightFromDeltaMaterial(pool, record.point, record.reflect);
        }
        else
        {
            // warning: record.f above should be recaculated,it's OK here because we only have lambert material
            // to be fixed later when more material types are supported
            color += beta * record.f * sampleLightFromNormalMaterial(pool, record.point, record.normal);
        }

        beta *= (record.f * record.dot);
        hitRay = genNextRay(record);

        // bug? why?
        // to bright because of the lack of attenuation factor
        // float p = 1.0f - beta.getClampedMaxComponent();
        float p = MathUtility::genRandomDecimal();
        if(m_rouletter.evaluate(p))
        {
            break;
        }
        beta /= p;
    }

    return color;
}

Color NeeTracer::sampleLightFromDeltaMaterial(std::shared_ptr<const ObjectPool> pool,
                                              const Vector3 &pos,
                                              const Vector3 &dir) const
{
    Ray deltaLightRay(pos, dir);
    Color lightColor = pool->getColorFromLight(deltaLightRay);

    return lightColor;
}

Color NeeTracer::sampleLightFromNormalMaterial(std::shared_ptr<const ObjectPool> pool,
                                               const Vector3 &pos,
                                               const Vector3 &normal) const
{
    float sampleLightPdf;
    Vector3 lightSurfacePoint = pool->m_pLight->sample(pos, sampleLightPdf);

    Vector3 lightDir = lightSurfacePoint - pos;
    lightDir.normalize();

    // plus lightDir * 0.001f is a hotfix to avoid self intersection
    Ray sampleLightRay(pos + lightDir * 0.001f, lightDir);
    Color lightColor = pool->getColorFromLight(sampleLightRay);

    // to be fixed later : test visibility with light first?
    float absDot = std::abs(normal * lightDir);

    // do half caculation here first
    return lightColor * (absDot / sampleLightPdf);
}

Ray NeeTracer::genNextRay(const HitRecord &record) const
{
    float sign = MathUtility::getSign(record.normal * record.reflect);

    //  multiply by a 0.001f is a lazy way to avoid self intersection
    Vector3 origin = record.point + sign * record.normal * 0.001f;

    return Ray(origin, record.reflect);
}
