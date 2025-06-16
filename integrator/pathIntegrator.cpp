#include "pathIntegrator.h"
#include <mathUtility.h>
#include <cassert>
#include <mathConstantDef.h>

Color PathIntegrator::Li(const Ray &ray, std::shared_ptr<const ObjectPool> pool) const
{
    Color color = Color::COLOR_BLACK;
    Color beta = Color::COLOR_WHITE;

    int depth = 0;
    Ray hitRay(ray);

    while (true)
    {
        if (depth > m_depth)
            break;
        depth++;

        Interaction interaction;

        if (!pool->hitScene(hitRay, interaction))
        {
            color += Color::COLOR_BLACK;
            break;
        }
        assert(interaction.primitive != nullptr);

        if(interaction.primitive->getMaterial() == nullptr)
        {
            color += Color::COLOR_BLACK;
            break;
        }


        //for debug
        assert(interaction.primitive->getMaterial() != nullptr);

        if (interaction.primitive->getMaterial()->isEmitting())
        {
            // color = interaction.material->getEmittedRadiance(); 
            color += beta * interaction.primitive->getMaterial()->getEmittedRadiance();
            break;
        }

        // if(interaction.normal_geometry.isSameDir(hitRay.dir))
        // {
            // color += Color::COLOR_BLACK;
            // break;
        // }

        std::unique_ptr<Bsdf> bsdf = interaction.primitive->getMaterial()->createBsdf(interaction);
        Vector3 wi;
        float _pdf;
        BxdfType sampledType;
        Color sampled_f = bsdf->sample_f(-hitRay.dir, wi, _pdf, sampledType, interaction, BxdfType::ALL);

        //  if(sampledType == BxdfType::REFLECTION)
        //  {
        //     assert(!hitRay.dir.isSameDir(interaction.normal_shading));
        //     assert(wo.isSameDir(interaction.normal_geometry));
        //  }

        Color _directLight = Color::COLOR_BLACK;
        
        Color f = Color::COLOR_BLACK;
        if(hasFlag(sampledType, BxdfType::DIFFUSE))
        {
            Ray rayToLight;
            _directLight = sampleLightFromNormalMaterial(pool, interaction.point, interaction.normal_shading, rayToLight);
            f = bsdf->f(-hitRay.dir, rayToLight.dir, BxdfType::DIFFUSE);
        }

        color += beta * f * _directLight;

        float cos_theta_incident_abs = std::abs(interaction.normal_geometry * wi);
        if (_pdf < 0.0000001f)//quick and dirty
        { 
            break;
        }
        beta *= (sampled_f * cos_theta_incident_abs) / _pdf;

        hitRay = genNextRay(interaction.point, interaction.normal_shading, wi);

    }

    return color;
}



Color PathIntegrator::sampleLightFromDeltaMaterial(std::shared_ptr<const ObjectPool> pool,
                                              const Vector3 &pos,
                                              const Vector3 &dir) const
{
    Ray deltaLightRay(pos, dir);
    Color lightColor = pool->getColorFromLight(deltaLightRay);

    return lightColor;
}

Color PathIntegrator::sampleLightFromNormalMaterial(std::shared_ptr<const ObjectPool> pool,
                                               const Vector3 &pos,
                                               const Vector3 &normal,
                                               Ray &sampleRay) const
{
    //for test
    // return Color::COLOR_WHITE * 100;

    float sampleLightPdf;
    Vector3 lightSurfacePoint = pool->light_->sample(pos, sampleLightPdf);

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

Ray PathIntegrator::genNextRay(const Vector3 &pos, const Vector3 &normal, const Vector3 &reflect) const
{
     float sign = MathUtility::getSign(normal * reflect);

    //  multiply by a 0.001f is a lazy way to avoid self intersection
    Vector3 origin = pos + sign * normal * 0.001f;

    return Ray(origin, reflect);
}