#include "neeVolTracer.h"
#include "hitrecord.h"
#include "mathUtility.h"
#include "mathConstantDef.h"

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
    float pdf = 1.0f;

    int depth = 0;
    Ray hitRay(ray);
    bool isVacuum = true;
    Color volF = Color::COLOR_WHITE;

    while (true)
    {
        if (depth > m_depth)
            break;
        depth++;

        if (isVacuum)
        {
            HitRecord record;
            if (!pool->hitScene(hitRay, record))
            {
                color += Color::COLOR_BLACK;
                break;
            }

            if (record.reflectPdf == 0.0f)
                break;

            pdf *= record.reflectPdf;
            normalTrace(pool, record, hitRay, beta, color, isVacuum, pdf);
        }
        else
        {
            volTrace(pool, hitRay, isVacuum, depth, beta, pdf, color);
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
    sampleRay = sampleLightRay; // return value
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
                                Color &color,
                                bool &isVacuum,
                                float &pdf) const
{
    // sample light
    if (record.isVolumeBoundery)
    {
        isVacuum = !isVacuum;
    }
    else if (record.isDelta)
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

void NeeVolTracer::volTrace(std::shared_ptr<const ObjectPool> pool,
                             Ray &hitRay,
                             bool &isVacuum,
                             int &depth,
                             Color &beta,
                             float &pdf,
                             Color &color) const
{
    // float pdf = 1.0f;
    // f = Color::COLOR_WHITE;

    while (!isVacuum)
    {
        // do tracing in volume
        // 1.get the longest distance to travel
        HitRecord record;
        if (!pool->hitScene(hitRay, record))
            break;

        if (!record.isVolumeBoundery)
            break;

        // the distance is record.t
        float tMax = record.t;
        Vector3 localPoint = record.geometry->getLocalPosition(record.point);
        float sigma_a = m_vox.get(localPoint.x, localPoint.y, localPoint.z);
        Media media(sigma_a, 1, Color::COLOR_NAVY);

        float sampleDistancePdf;
        float t = MathUtility::sampleExponential(media.sigma_major, sampleDistancePdf);
        pdf *= sampleDistancePdf;
        if (t > tMax)
        {
            Vector3 origin = record.point + hitRay.dir * MathConstant::FLOAT_SAMLL_NUMBER;
            hitRay.origin = origin;
            isVacuum = true;

            return;
        }

        int index = MathUtility::sampleFromWeights({media.sigma_a,
                                                    media.sigma_s,
                                                    media.sigma_n});

        if (index == 0)
        {
            // dirty but quick fix,should be fixed later
            pdf *= (media.sigma_a / media.sigma_major);
            return;
        }
        else if (index == 1)
        {
            depth++;
            if (depth > m_depth)
                return;

            pdf *= (media.sigma_s / media.sigma_major);
            // todo: get color from light
            Vector3 pos = hitRay.getPosition(t);
            float sampleLightPdf;
            Vector3 lightSurfacePoint = pool->m_pLight->sample(pos, sampleLightPdf);
            Vector3 lightDir = lightSurfacePoint - pos;
            lightDir.normalize();
            Ray sampleLightRay(pos, lightDir);
            Color lightColor = pool->getColorFromLight(sampleLightRay);
            if (lightColor == Color::COLOR_BLACK)
            {
                // blocked by some object
            }
            else
            {
                // 0.get max distance to the volume boundery
                HitRecord bounderyRecord;
                if (!pool->hitScene(sampleLightRay, bounderyRecord))
                {
                }
                else
                {
                    float tBounderyMax = record.t;
                    float n_t = 0.0f;
                    while (n_t < tBounderyMax)
                    {
                        sampleLightPdf *= (media.sigma_n / media.sigma_major);
                        float n_l_samplePdf;
                        n_t += 50 * MathUtility::sampleExponential(media.sigma_major, n_l_samplePdf);
                    }
                    Ray vaccumRay(hitRay.getPosition(tBounderyMax) + lightDir * MathConstant::FLOAT_SAMLL_NUMBER, lightDir);
                    Color vaccumLightColor = pool->getColorFromLight(sampleLightRay);
                    Color finalColor = vaccumLightColor * beta / sampleLightPdf;
                    color += finalColor;
                }
            }

            // scattering
            Vector3 dir = Vector3::sampleUniformFromSphere();
            pdf *= MathConstant::FOUR_PI;
            beta = beta * MathConstant::FOUR_PI;
            Ray newRay(hitRay.getPosition(t), dir);
        }
        else
        {
            pdf *= (media.sigma_n / media.sigma_major);
            float n_samplePdf;
            t += 50 * MathUtility::sampleExponential(media.sigma_major, n_samplePdf);
        }
    }

    return;
}