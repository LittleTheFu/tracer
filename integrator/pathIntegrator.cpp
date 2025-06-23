#include "pathIntegrator.h"
#include "mathUtility.h"
#include <cassert>
#include "mathConstantDef.h"
#include "mediumInteraction.h"
#include "medium.h"

PathIntegrator::PathIntegrator(int depth) : depth_(depth)
{
    assert(depth_ > 2);
}

Color PathIntegrator::Li(const Ray &ray, std::shared_ptr<const ObjectPool> pool) const
{
    Color color = Color::COLOR_BLACK;
    Color beta = Color::COLOR_WHITE; // 路径权重 / 吞吐量

    int depth = 0;
    Ray hitRay(ray);

    while (true)
    {
        if (depth > depth_) break;
        depth++;

        Interaction interaction;
        if (!pool->hitScene(hitRay, interaction))
        {
            // 如果光线未击中任何表面，并且还在介质中，需要处理介质到无限远的透射贡献
            // 对于体积路径追踪，这通常意味着介质边界是无限远，或者有环境光
            // 在这里简单 break 可能导致偏差，取决于你的场景设定。
            // 假设此时光线离开了所有介质和物体，直接累积环境光并break
            // color += beta * getEnvironmentLight(hitRay.dir); // 示例：累积环境光
            break; 
        }
        
        assert(interaction.primitive != nullptr);

        float tMax = interaction.t; // 到表面交点的距离

        if (hitRay.medium) // 如果光线当前在介质中
        {
            MediumInteraction mediumInteraction;
            // 调用 sample 函数，期望它返回散射事件或穿透事件的 PDF
            float sampledPdf = hitRay.medium->sample(hitRay, tMax, mediumInteraction); 
            
            // **核心修正：根据 mediumInteraction.isValid() 的状态来更新 beta 和计算贡献**
            if (mediumInteraction.isValid()) // **发生了真实介质交互（散射或吸收）**
            {
                // 此时，光线在 mediumInteraction.t 处停止了。
                // 如果 sample 返回 0 (表示吸收)，则路径终止。
                if (sampledPdf < MathConstant::FLOAT_SMALL_NUMBER) { // 吸收发生
                    break; 
                }

                // 路径权重更新：beta /= sampledPdf;
                // beta 包含了光线从起点到上一个点（或介质入口）的吞吐量。
                // 现在光线在介质中发生了散射，我们需要除以采样的 PDF。
                beta /= sampledPdf; 

                // 散射贡献计算：
                // 注意：由于 sample 函数已经返回了完整的 P_scatter(t)，
                // 这里的贡献计算不应该再乘以额外的 transmittance 或 sigmaS。
                // 贡献 = beta * L_light_sampled_from_volume * phaseFunction
                // 这里的 L_light_sampled_from_volume 是直接光照或间接光照的估算。
                
                float phaseFunctionVal = 1.0f / (4.0f * MathConstant::PI); // 各向同性相函数

                // sampleLightFromNormalMaterial 是对直接光照的采样
                Ray _volumeRayToLight;
                Color _light = sampleLightFromNormalMaterial(pool,
                                                              mediumInteraction.point,
                                                              Vector3::ZERO, // 散射点没有法线概念，可以传零向量
                                                              _volumeRayToLight,
                                                              true); // 假设这是从介质中向光源采样

                // 直接光照贡献：beta * (直接光) * 相函数
                // 这里的 _light 已经包含了光源的 Le 和 PDF。
                // 如果 _light 是 Li * abs(dot(wi, N)) / pdf_light，那么这里就是 Li * phaseFunction * (abs(dot(wi, N)) / pdf_light)
                // 假设 _light 已经包含了必要的 pdf_light
                color += beta * _light * phaseFunctionVal; 

                // 更新光线，从散射点开始新的路径
                Vector3 newDir = Vector3::sampleUniformFromSphere(); // 从相函数采样新的出射方向
                hitRay.origin = mediumInteraction.point;
                hitRay.dir = newDir;
                hitRay.medium = mediumInteraction.medium; // 光线仍在当前介质中
                
                continue; // 继续下一轮迭代
            }
            else // **光线穿透介质，没有在 tMax 之前发生介质交互**
            {
                // 此时 sampledPdf 就是 transmittance(hitRay, tMax)
                // 路径权重更新：beta /= sampledPdf
                // 这使得 beta 抵消了从 hitRay.origin 到 tMax 的介质透射，从而只保留了之前的权重
                // 这是正确的，因为光线现在是“透明地”穿过介质，到达了表面。
                if (sampledPdf < MathConstant::FLOAT_SMALL_NUMBER) break; // 如果透射率为 0，则路径终止
                beta /= sampledPdf; 

                // 光线到达表面，继续执行 surface hit 逻辑。
                // hitRay 和 interaction 保持不变，因为它们指向了表面交点。
                // 无需 continue，直接进入下面的 if (interaction.is_surface_hit) 块。
            }
        }
        else
        {
            // in vacuum, do nothing
        }

        if (interaction.is_surface_hit)
        {
            if (interaction.primitive->getMaterial() == nullptr)
            {
                // for debug
                assert(0);
                break;
            }

            // for debug
            assert(interaction.primitive->getMaterial() != nullptr);

            if (interaction.primitive->getMaterial()->isEmitting())
            {
                color += beta * interaction.primitive->getMaterial()->getEmittedRadiance();
                break;
            }

            // sample from bsdf
            std::unique_ptr<Bsdf> bsdf = interaction.primitive->getMaterial()->createBsdf(interaction);
            Vector3 wi;
            float _pdf;
            BxdfType sampledType;
            Color sampled_f = bsdf->sample_f(-hitRay.dir, wi, _pdf, sampledType, interaction, BxdfType::ALL);

            // sample from light
            Color _directLight = Color::COLOR_BLACK;
            Color f = Color::COLOR_BLACK;
            if (hasFlag(sampledType, BxdfType::DIFFUSE))
            {
                Ray rayToLight;
                _directLight = sampleLightFromNormalMaterial(pool,
                                                             interaction.point,
                                                             interaction.normal_shading,
                                                             rayToLight, false);
                f = bsdf->f(-hitRay.dir, rayToLight.dir, BxdfType::DIFFUSE);
            }
            color += beta * f * _directLight;

            float cos_theta_incident_abs = std::abs(interaction.normal_geometry * wi);
            if (_pdf < 0.0000001f) // quick and dirty
            {
                break;
            }

            if (hasFlag(sampledType, BxdfType::SPECULAR))
            {
                beta *= (sampled_f);
            }
            else
            {
                beta *= (sampled_f * cos_theta_incident_abs) / _pdf;
            }

            hitRay = genNextRay(interaction.point, interaction.normal_shading, wi);
        }
        else if (interaction.is_volume_boundary_hit)
        {
            hitRay.origin = interaction.point + hitRay.dir * MathConstant::FLOAT_SMALL_NUMBER;

            if (hitRay.medium)
                hitRay.medium = nullptr;
            else
                hitRay.medium = interaction.medium;
        }
    }

    return color;
}

// Color PathIntegrator::sampleLightFromDeltaMaterial(std::shared_ptr<const ObjectPool> pool,
//                                                    const Vector3 &pos,
//                                                    const Vector3 &dir) const
// {
//     Ray deltaLightRay(pos, dir);
//     Color lightColor = pool->getColorFromLight(deltaLightRay);

//     return lightColor;
// }

Color PathIntegrator::sampleLightFromNormalMaterial(std::shared_ptr<const ObjectPool> pool,
                                                    const Vector3 &pos,
                                                    const Vector3 &normal,
                                                    Ray &sampleRay,
                                                    bool isVolumetricPoint) const
{
    // for test
    //  return Color::COLOR_WHITE * 100;
    std::vector<std::shared_ptr<AreaLight>> lights = pool->getLights();
    int lightNum = static_cast<int>(lights.size());
    if (lightNum == 0)
    {
        return Color::COLOR_BLACK;
    }
    int lightIndex = MathUtility::sampleUniformly(lightNum);
    float lightPickPdf = 1.0f / lightNum;

    float sampleLightPdf;
    Vector3 lightSurfacePoint = lights.at(lightIndex)->sample(pos, sampleLightPdf);
    Vector3 lightDir = lightSurfacePoint - pos;
    lightDir.normalize();

    // plus lightDir * 0.001f is a hotfix to avoid self intersection
    Ray sampleLightRay(pos + lightDir * 0.001f, lightDir);
    sampleRay = sampleLightRay; // return value
    Color lightColor = pool->getColorFromLight(sampleLightRay, lightIndex);

    // to be fixed later : test visibility with light first?
    float absDot = std::abs(normal * lightDir);

    // warning: an ugly hotfix for test volume rendering
    if (isVolumetricPoint)
        absDot = 1.0f;

    // assert(MathUtility::is_in_range(lightColor.r, 99.99f, 100.01f, false, false));
    // assert(MathUtility::is_in_range(lightColor.g, 99.99f, 100.01f, false, false));
    // assert(MathUtility::is_in_range(lightColor.b, 99.99f, 100.01f, false, false));

    // do half caculation here first
    return lightColor * (absDot / (sampleLightPdf * lightPickPdf));
}

Ray PathIntegrator::genNextRay(const Vector3 &pos, const Vector3 &normal, const Vector3 &reflect) const
{
    float sign = MathUtility::getSign(normal * reflect);

    //  multiply by a 0.001f is a lazy way to avoid self intersection
    Vector3 origin = pos + sign * normal * 0.001f;

    return Ray(origin, reflect);
}