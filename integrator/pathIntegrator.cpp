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

        HitRecord record;
        Interaction interaction;

        if (!pool->hitScene(hitRay, record, interaction))
        {
            color += Color::COLOR_BLACK;
            break;
        }

        if(interaction.material == nullptr)
        {
            color += Color::COLOR_BLACK;
            break;
        }



        assert(interaction.material != nullptr);
        std::unique_ptr<Bsdf> bsdf = interaction.material->createBsdf(interaction);
        Vector3 wo;
        float _pdf;
        Color f = bsdf->sample_f(-hitRay.dir, wo, _pdf, BxdfType::ALL);

        Ray dummyRay;
        Color _directLight = sampleLightFromNormalMaterial(pool, interaction.point, interaction.normal_shading, dummyRay);
        // _directLight = Color::COLOR_WHITE * 100;


        color += beta * f * _directLight;

        beta *= (f * record.dot) / _pdf;

        HitRecord nextRecord;
        nextRecord.point = interaction.point;
        nextRecord.normal = interaction.normal_shading;
        nextRecord.reflect = wo;
        hitRay = genNextRay(nextRecord);
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

Ray PathIntegrator::genNextRay(const HitRecord &record) const
{
    float sign = MathUtility::getSign(record.normal * record.reflect);

    //  multiply by a 0.001f is a lazy way to avoid self intersection
    Vector3 origin = record.point + sign * record.normal * 0.001f;

    return Ray(origin, record.reflect);
}

void PathIntegrator::getLocalWoWi(const HitRecord &record, const Vector3 &worldWo, const Vector3 &worldWi, Vector3 &wo, Vector3 &wi) const
{
    Frame frame(record.normal, record.point);

    wo = frame.vectorToLocal(worldWo);
    wi = frame.vectorToLocal(worldWi);

    wo.normalize();
    wi.normalize();
}
