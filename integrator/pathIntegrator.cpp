#include "pathIntegrator.h"
#include "mathUtility.h"
#include <cassert>
#include "mathConstantDef.h"
#include "mediumInteraction.h"
#include "medium.h"
#include "mediumBoundary.h"

PathIntegrator::PathIntegrator(int depth) : depth_(depth)
{
    assert(depth_ > 2);
}

Color PathIntegrator::Li(const Ray &ray, std::shared_ptr<const ObjectPool> pool) const
{
    Color color = Color::COLOR_BLACK;
    Color beta = Color::COLOR_WHITE;

    int depth = 0;
    Ray hitRay(ray);

    while (true)
    {
        if (depth >= depth_) break;

        Interaction interaction;
        bool hitScene = pool->hitScene(hitRay, interaction);
        float tMax = hitScene ? interaction.t : MathConstant::FLOAT_MAX;

        // if (hitRay.medium && !hitRay.medium->isVaccum())
        if (hitRay.medium)
        {
            MediumInteraction mediumInteraction;
            MediumEventType eventType = hitRay.medium->sample(hitRay, tMax, mediumInteraction);

            if (eventType == MediumEventType::Scatter)
            {
                depth++;

                float sigma_s = hitRay.medium->getSigmaS(mediumInteraction.point);
                float sigma_t_majorant = hitRay.medium->getSigmaT(mediumInteraction.point);

                beta *= (sigma_s / sigma_t_majorant);

                float phaseFunctionVal = 1.0f / (4.0f * MathConstant::PI);
                Ray _volumeRayToLight;
                Color _light = sampleLightFromNormalMaterial(pool, mediumInteraction.point, Vector3::ZERO, _volumeRayToLight, true);
                color += beta * _light * phaseFunctionVal;

                Vector3 newDir = Vector3::sampleUniformFromSphere();
                float phasePdf = 1.0f / (4.0f * MathConstant::PI);
                beta *= (phaseFunctionVal / phasePdf);

                hitRay.origin = mediumInteraction.point;
                hitRay.dir = newDir;

                continue;
            }
            else if (eventType == MediumEventType::Absorb)
            {
                break;
            }
        }

        if (!hitScene)
        {
            break;
        }

        if (interaction.is_surface_hit)
        {
            depth++;

            if (interaction.primitive->getMaterial()->isEmitting())
            {
                if (depth == 1 || !hitRay.medium) {
                    color += beta * interaction.primitive->getMaterial()->getEmittedRadiance();
                }
                break;
            }

            std::unique_ptr<Bsdf> bsdf = interaction.primitive->getMaterial()->createBsdf(interaction);
            Color _directLight = Color::COLOR_BLACK;

            if (!bsdf->hasSpecular()) {
                Ray rayToLight;
                _directLight = sampleLightFromNormalMaterial(pool, interaction.point, interaction.normal_shading, rayToLight, false);
                Color f = bsdf->f(-hitRay.dir, rayToLight.dir, BxdfType::ALL_NON_SPECULAR);
                color += beta * f * _directLight;
            }

            Vector3 wi;
            float _pdf;
            BxdfType sampledType;
            Color sampled_f = bsdf->sample_f(-hitRay.dir, wi, _pdf, sampledType, interaction, BxdfType::ALL);

            // if (_pdf < MathConstant::FLOAT_SMALL_NUMBER || sampled_f.isBlack())
            if (sampled_f.isBlack())
            {
                break;
            }

            if (hasFlag(sampledType, BxdfType::SPECULAR))
            {
                beta *= (sampled_f);
            }
            else
            {
                float cos_theta_incident_abs = std::abs(interaction.normal_shading.dot(wi));
                Color tmp = (sampled_f * cos_theta_incident_abs) / _pdf;//debug
                beta *= tmp;
            }
        
            hitRay = genNextRay(interaction.point, interaction.normal_shading, wi);
        }
        else if (interaction.is_volume_boundary_hit)
        {
            hitRay.origin = interaction.point + hitRay.dir * MathConstant::FLOAT_SMALL_NUMBER;
            // if (hitRay.medium)//here, it should be replaced with mediumBoundary...
            //     hitRay.medium = nullptr;
            // else
            //     hitRay.medium = interaction.medium;

            //right now we are assuming there is medium everywhere
            if (interaction.isHitFromOutside())
            {
                hitRay.medium = interaction.mediumBoundary->mediumInside_;
            }
            else
            {
                hitRay.medium = interaction.mediumBoundary->mediumOutside_;
            }

            continue;
        }
    }

    return color;
}

Color PathIntegrator::sampleLightFromNormalMaterial(std::shared_ptr<const ObjectPool> pool,
                                                   const Vector3 &pos,
                                                   const Vector3 &normal,
                                                   Ray &sampleRay,
                                                   bool isVolumetricPoint) const
{
    std::vector<std::shared_ptr<AreaLight>> lights = pool->getLights();
    int lightNum = static_cast<int>(lights.size());
    if (lightNum == 0)
    {
        return Color::COLOR_BLACK;
    }
    int lightIndex = MathUtility::sampleUniformly(lightNum);
    float lightPickPdf = 1.0f / lightNum;

    //take care of the pdf here
    float sampleLightPdf;
    Vector3 lightNormal;
    Vector3 lightSurfacePoint = lights.at(lightIndex)->sample(pos, sampleLightPdf, lightNormal);
    lightNormal.normalize();
    float d2 = (lightSurfacePoint - pos).lenthSq();
 
    Vector3 lightDir = lightSurfacePoint - pos;
    lightDir.normalize();

    float lightDot = std::abs(lightNormal.dot(lightDir));


    Ray sampleLightRay(pos + lightDir * 0.001f, lightDir);
    sampleRay = sampleLightRay;

    Color lightColor = pool->getColorFromLight(sampleLightRay, lightIndex);

    if (lightColor.isBlack()){
        return Color::COLOR_BLACK;
    }

    float absDot = std::abs(normal.dot(lightDir));
    if (isVolumetricPoint)
    {
        absDot = 1.0f;
    }
    
    if(sampleLightPdf < MathConstant::FLOAT_SMALL_NUMBER || lightPickPdf < MathConstant::FLOAT_SMALL_NUMBER){
        return Color::COLOR_BLACK;
    }

    return lightColor * (absDot / (sampleLightPdf * lightPickPdf * d2)) * lightDot;
}

Ray PathIntegrator::genNextRay(const Vector3 &pos, const Vector3 &normal, const Vector3 &reflect) const
{
    float sign = (normal.dot(reflect) > 0) ? 1.0f : -1.0f;
    Vector3 origin = pos + sign * normal * 0.001f;
    return Ray(origin, reflect);
}
