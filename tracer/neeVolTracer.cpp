#include "neeVolTracer.h"
#include "hitrecord.h"
#include "mathUtility.h"
#include "mathConstantDef.h"

NeeVolTracer::NeeVolTracer(int depth)
{
    if (depth >= 1)
        m_depth = depth;

    n_trave_factor = 200;
    m_vox_factor = 1;
}

Color NeeVolTracer::trace(std::shared_ptr<const ObjectPool> pool, Ray &ray) const
{
    bool isAbsorbed = false;

    // Color color = Color::COLOR_BLACK;
    Color color = traceFirstBounce(pool, ray);
    Color beta = Color::COLOR_WHITE;
    float pdf = 1.0f;

    int depth = 0;
    Ray hitRay(ray);
    bool isVacuum = true;
    Color volF = Color::COLOR_WHITE;
    bool isPassingVolume = false;

    while (true)
    {
        if (isAbsorbed)
            break;

        if (depth > m_depth)
            break;

        if (!isPassingVolume)
            depth++;

        if (isVacuum)
        {
            HitRecord record;
            if (!pool->hitScene(hitRay, record))
            {
                color += Color::COLOR_BLACK;
                break;
            }

            if (record.reflectPdf == 0.0f && !record.isVolumeBoundery)
                break;

            if (record.isVolumeBoundery)
                record.reflectPdf = 1.0f;

            pdf *= record.reflectPdf;
            evalVaccum(pool, record, hitRay, beta, color, isVacuum, pdf, isPassingVolume);
        }
        else
        {
            evalVolume(pool, hitRay, isVacuum, depth, beta, pdf, color, isAbsorbed, isPassingVolume);
        }
    }

    // if(isAbsorbed)
    //     color = Color::COLOR_BLACK;

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

    // do partical caculation here first
    Color retColor = lightColor * (absDot / sampleLightPdf);
    if (retColor == Color::COLOR_BLACK)
    {
        int k = 3;
    }
    return retColor;
}

Ray NeeVolTracer::genNextRay(const HitRecord &record) const
{
    float sign = MathUtility::getSign(record.normal * record.reflect);

    //  multiply by a 0.001f is a lazy way to avoid self intersection
    Vector3 origin = record.point + sign * record.normal * 0.001f;

    return Ray(origin, record.reflect);
}

Color NeeVolTracer::evalVaccum(std::shared_ptr<const ObjectPool> pool,
                               const HitRecord &record,
                               Ray &hitRay,
                               Color &beta,
                               Color &color,
                               bool &isVacuum,
                               float &pdf,
                               bool &isPassingVolume) const
{
    isPassingVolume = false;
    Vector3 old_ray_dir = hitRay.dir;
    // sample light
    if (record.isVolumeBoundery)
    {
        isPassingVolume = true;
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

        if (color == Color::COLOR_BLACK)
        {
            int k = 3;
        }
    }

    beta *= (record.f * record.dot);
    hitRay = genNextRay(record);

    if (record.isVolumeBoundery)
    {
        hitRay.origin = record.point + old_ray_dir;
        hitRay.dir = old_ray_dir;
    }

    return color;
}

void NeeVolTracer::evalVolume(std::shared_ptr<const ObjectPool> pool,
                              Ray &hitRay,
                              bool &isVacuum,
                              int &depth,
                              Color &beta,
                              float &pdf,
                              Color &color,
                              bool &isAbsorbed,
                              bool &isPassingVolume) const
{
    // float pdf = 1.0f;
    // f = Color::COLOR_WHITE;
    isPassingVolume = false;

    while (!isVacuum)
    {
        // do tracing in volume
        // 1.get the longest distance to travel
        HitRecord record;
        if (!pool->hitScene(hitRay, record))
        {
            isVacuum = true;
            return;
        }

        // if (!record.isVolumeBoundery)
        //     break;

        // the distance is record.t
        float tMax = record.t;
        Vector3 localPoint = record.geometry->getLocalPosition(record.point);
        // float sigma_s = m_vox.get(localPoint.x * m_vox_factor, localPoint.y * m_vox_factor, localPoint.z * m_vox_factor);
        float sigma_s = m_noise_s.getValue(localPoint)/2;
        float sigma_a = m_noise_a.getValue(localPoint)/50;
        Media media(sigma_a, sigma_s, Color::COLOR_NAVY);

        float sampleDistancePdf;
        float t = MathUtility::sampleExponential(media.sigma_major, sampleDistancePdf);
        pdf *= sampleDistancePdf;
        if (t > tMax)
        {
            Vector3 origin = record.point + hitRay.dir;
            hitRay.origin = origin;
            isPassingVolume = true;
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
            isAbsorbed = true;
            // color += Color::COLOR_BLACK;
            // color = Color::COLOR_YELLOW;
            isPassingVolume = false;
            return;
        }
        else if (index == 1)
        {
            depth++;
            if (depth > m_depth)
            {
                isPassingVolume = false;
                return;
            }

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
                    float tBounderyMax = bounderyRecord.t;
                    float n_t = 0.0f;
                    while (n_t < tBounderyMax)
                    {
                        Vector3 currentPos = sampleLightRay.getPosition(n_t);
                        Vector3 _localPoint = record.geometry->getLocalPosition(currentPos);
                        // float _sigma_s = m_vox.get(_localPoint.x * m_vox_factor, _localPoint.y * m_vox_factor, _localPoint.z * m_vox_factor);
                        float sigma_s = m_noise_s.getValue(localPoint)/2;
                        float sigma_a = m_noise_a.getValue(localPoint)/50;
                        Media _media(sigma_a, sigma_s, Color::COLOR_NAVY);
                        sampleLightPdf *= (_media.sigma_n / _media.sigma_major);
                        float n_l_samplePdf;
                        n_t += n_trave_factor * MathUtility::sampleExponential(_media.sigma_major, n_l_samplePdf);
                        sampleLightPdf *= n_l_samplePdf;
                    }
                    // Ray vaccumRay(sampleLightRay.getPosition(tBounderyMax) + lightDir * MathConstant::FLOAT_SAMLL_NUMBER, lightDir);
                    Ray vaccumRay(sampleLightRay.getPosition(tBounderyMax) + lightDir, lightDir);
                    Color vaccumLightColor = pool->getColorFromLight(sampleLightRay);
                    Color finalColor = vaccumLightColor * beta / sampleLightPdf;
                    // Color finalColor = vaccumLightColor;
                    color += finalColor;
                    // color += Color::COLOR_WHITE;
                }
            }

            // scattering
            Vector3 dir = Vector3::sampleUniformFromSphere();
            pdf *= MathConstant::FOUR_PI;
            beta = beta * MathConstant::FOUR_PI;
            Ray newRay(hitRay.getPosition(t), dir);
            hitRay.origin = newRay.origin;
            hitRay.dir = newRay.dir;

            HitRecord _record;
            if (!pool->hitScene(hitRay, _record))
            {
            }
            else
            {
                tMax = _record.t;
            }
        }
        else
        {
            pdf *= (media.sigma_n / media.sigma_major);
            float n_samplePdf;
            t += n_trave_factor * MathUtility::sampleExponential(media.sigma_major, n_samplePdf);
            pdf *= n_samplePdf;
            if (t > tMax)
            {
                isVacuum = true;
                isPassingVolume = true;
                hitRay.origin = hitRay.getPosition(tMax) + hitRay.dir;
                return;
            }
        }
    }

    isPassingVolume = false;
    return;
}
