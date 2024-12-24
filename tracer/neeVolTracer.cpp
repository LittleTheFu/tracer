#include "neeVolTracer.h"
#include "hitrecord.h"
#include "mathUtility.h"

NeeVolTracer::NeeVolTracer(int depth)
{
    if (depth > 1)
        m_depth = depth;
}

Color NeeVolTracer::trace(std::shared_ptr<const ObjectPool> pool, Ray &ray) const
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

        if(record.reflectPdf == 0.0f)
            break;

        if(record.isVolumeBoundery)
        {

        }
        else
        {
            normalTrace(pool, record, hitRay, beta, color);
        }
    }

    return color;
}

Color NeeVolTracer::sampleLightFromDeltaMaterial(std::shared_ptr<const ObjectPool> pool,
                                              const Vector3 &pos,
                                              const Vector3 &dir) const
{
    Ray deltaLightRay(pos, dir);
    Color lightColor = pool->getColorFromLight(deltaLightRay);

    return lightColor;
}

Color NeeVolTracer::sampleLightFromNormalMaterial(std::shared_ptr<const ObjectPool> pool,
                                               const Vector3 &pos,
                                               const Vector3 &normal,
                                               Ray &sampleRay) const
{
    float sampleLightPdf;
    Vector3 lightSurfacePoint = pool->m_pLight->sample(pos, sampleLightPdf);

    Vector3 lightDir = lightSurfacePoint - pos;
    lightDir.normalize();

    // plus lightDir * 0.001f is a hotfix to avoid self intersection
    Ray sampleLightRay(pos + lightDir * 0.001f, lightDir);
    sampleRay = sampleLightRay;//return value
    Color lightColor = pool->getColorFromLight(sampleLightRay);

    // to be fixed later : test visibility with light first?
    float absDot = std::abs(normal * lightDir);

    // do half caculation here first
    return lightColor * (absDot / sampleLightPdf);
}

Ray NeeVolTracer::genNextRay(const HitRecord &record) const
{
    float sign = MathUtility::getSign(record.normal * record.reflect);

    //  multiply by a 0.001f is a lazy way to avoid self intersection
    Vector3 origin = record.point + sign * record.normal * 0.001f;

    return Ray(origin, record.reflect);
}

Color NeeVolTracer::normalTrace(std::shared_ptr<const ObjectPool> pool,
                                const HitRecord &record,
                                Ray &hitRay,
                                Color &beta,
                                Color &color) const
{
    // sample light
    if (record.isDelta)
    {
        color += beta * sampleLightFromDeltaMaterial(pool, record.point, record.reflect);
    }
    else
    {
        // to be fixed later:here you need to check if the pointer is null

        Ray sampleRay;
        Color partialColor = sampleLightFromNormalMaterial(pool, record.point, record.normal, sampleRay);

        Frame frame(record.normal, record.point);
        Vector3 local_wo = frame.vectorToLocal(-hitRay.dir);
        Vector3 local_wi = frame.vectorToLocal(sampleRay.dir);
        local_wo.normalize();
        local_wi.normalize();
        Color clr = record.brdf->get_f(local_wo, local_wi);
        color += beta * clr * partialColor;
    }

    beta *= (record.f * record.dot);
    hitRay = genNextRay(record);

    return color;
}
