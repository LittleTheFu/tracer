#include "pathIntegrator.h"
#include <mathUtility.h>
#include <cassert>

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
            color += interaction.primitive->getMaterial()->getEmittedRadiance();
            break;
        }

        if(interaction.normal_geometry.isSameDir(hitRay.dir))
        {
            // color += Color::COLOR_BLACK;
            break;
        }

        std::unique_ptr<Bsdf> bsdf = interaction.primitive->getMaterial()->createBsdf(interaction);
        Vector3 wo;
        float _pdf;
        Color f = bsdf->sample_f(hitRay.dir, wo, _pdf, interaction, BxdfType::ALL);

        Ray dummyRay;
        Color _directLight = sampleLightFromNormalMaterial(pool, interaction.point, interaction.normal_shading, dummyRay);
        // _directLight = Color::COLOR_WHITE * 100;


        color += beta * f * _directLight;

        float dot = std::abs(interaction.normal_geometry * hitRay.dir);
        beta *= (f * dot) / _pdf;

        hitRay = genNextRay(interaction.point, interaction.normal_shading, wo);

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
    Vector3 origin = pos + sign * reflect * 0.001f;

    return Ray(origin, reflect);
}