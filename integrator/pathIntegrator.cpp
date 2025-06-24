#include "pathIntegrator.h"
#include "mathUtility.h"
#include <cassert>
#include "mathConstantDef.h"
#include "mediumInteraction.h"
#include "medium.h" // 确保包含了 medium.h 以获取 MediumEventType

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
        if (depth >= depth_) break; // 使用 >= 更安全

        Interaction interaction;
        bool hitScene = pool->hitScene(hitRay, interaction);

        // 查找光线与表面的最近交点
        // 如果没有交点，tMax 为无穷大
        float tMax = hitScene ? interaction.t : MathConstant::FLOAT_MAX;

        if (hitRay.medium) // 如果光线当前在介质中
        {
            MediumInteraction mediumInteraction;
            // 调用新的 sample 函数，它返回一个清晰的事件类型
            MediumEventType eventType = hitRay.medium->sample(hitRay, tMax, mediumInteraction);

            if (eventType == MediumEventType::Scatter)
            {
                // **[核心修正]** 处理散射事件
                depth++; // 介质中的散射也算一次弹射

                // 获取散射点的属性
                float sigma_s = hitRay.medium->getSigmaS(mediumInteraction.point);
                // 假设是均匀介质，majorant 等于真实 sigma_t
                float sigma_t_majorant = hitRay.medium->getSigmaT(mediumInteraction.point);

                // Ratio Tracking 的权重更新：beta *= (sigma_s / sigma_t_majorant)
                // 这个权重已经隐式地包含了到散射点的透射率！
                beta *= (sigma_s / sigma_t_majorant);

                // --- 直接光照估计 (Next Event Estimation, NEE) ---
                float phaseFunctionVal = 1.0f / (4.0f * MathConstant::PI); // 各向同性相函数
                Ray _volumeRayToLight;
                Color _light = sampleLightFromNormalMaterial(pool,
                                                            mediumInteraction.point,
                                                            Vector3::ZERO, // 散射点没有法线
                                                            _volumeRayToLight,
                                                            true); // 告知是体积点
                // 累加直接光贡献。_light 已经包含了 Le * G * Tr_shadow / pdf_light
                color += beta * _light * phaseFunctionVal;

                // --- 为下一次弹射准备 (间接光) ---
                // 从相函数采样新的出射方向 (这里用各向同性)
                Vector3 newDir = Vector3::sampleUniformFromSphere();
                float phasePdf = 1.0f / (4.0f * MathConstant::PI);
                
                // 更新 beta 以包含相函数项 (phase / pdf)
                // 对于各向同性，这两项相等，所以 beta 不变
                beta *= (phaseFunctionVal / phasePdf);
                
                // 更新光线，从散射点开始新的路径
                hitRay.origin = mediumInteraction.point;
                hitRay.dir = newDir;
                // hitRay.medium 保持不变

                continue; // 继续追踪新光线
            }
            else if (eventType == MediumEventType::Absorb)
            {
                // **[核心修正]** 处理吸收事件
                break; // 路径被吸收，终止
            }
            // else if (eventType == MediumEventType::Transmit)
            // {
            //     // **[核心修正]** 处理穿透事件
            //     // 光线成功到达了 tMax 处的表面，没有发生真实交互。
            //     // 使用 Delta Tracking 时，beta 在这里【不需要】任何更新！
            //     // 路径的衰减已经通过 null collision 隐式地处理了。
            //     // 我们只需要让代码继续执行到下面的 surface hit 逻辑即可。
            // }
        }

        // 如果没有命中任何物体（包括介质边界），则路径飞出场景
        if (!hitScene)
        {
            // 在这里可以添加环境光
            // color += beta * getEnvironmentLight(hitRay.dir);
            break;
        }

        // --- 至此，光线已经到达了一个表面 ---

        if (interaction.is_surface_hit)
        {
            depth++; // 表面交互算一次弹射

            assert(interaction.primitive->getMaterial() != nullptr);

            // 1. 处理自发光表面
            if (interaction.primitive->getMaterial()->isEmitting())
            {
                // 只有当是第一次弹射时才添加自发光，或者从介质出来直接看到光源
                // 否则 NEE 会计算它。这是一个简化，可以防止重复计算。
                // 严格来说，需要检查前一个事件是否是 Specular/Delta。
                if (depth == 1 || !hitRay.medium) {
                     color += beta * interaction.primitive->getMaterial()->getEmittedRadiance();
                }
                break;
            }

            // 2. 表面散射
            // a. 直接光照 (NEE)
            std::unique_ptr<Bsdf> bsdf = interaction.primitive->getMaterial()->createBsdf(interaction);
            Color _directLight = Color::COLOR_BLACK;
            // 只对非镜面材质做NEE
            if (bsdf->hasNonSpecular()) {
                Ray rayToLight;
                _directLight = sampleLightFromNormalMaterial(pool, interaction.point, interaction.normal_shading, rayToLight, false);
                Color f = bsdf->f(-hitRay.dir, rayToLight.dir, BxdfType::ALL_NON_SPECULAR);
                color += beta * f * _directLight;
            }
            
            // b. 间接光照 (BSDF 采样)
            Vector3 wi;
            float _pdf;
            BxdfType sampledType;
            Color sampled_f = bsdf->sample_f(-hitRay.dir, wi, _pdf, sampledType, interaction, BxdfType::ALL);

            if (_pdf < MathConstant::FLOAT_SMALL_NUMBER || sampled_f.isBlack())
            {
                break;
            }
            
            float cos_theta_incident_abs = std::abs(interaction.normal_shading.dot(wi));
            
            // 更新路径权重 beta
            beta *= (sampled_f * cos_theta_incident_abs) / _pdf;
            
            // 更新光线
            hitRay = genNextRay(interaction.point, interaction.normal_shading, wi);
            // 处理介质边界转换
            // if(interaction.primitive->getMaterial()->isTransition()){
            //     // 如果当前在介质中，则离开；如果不在，则进入
            //     hitRay.medium = hitRay.medium ? nullptr : interaction.primitive->getMediumInterface().getMedium(interaction.normal_geometry, wi);
            // }

        }
        else if (interaction.is_volume_boundary_hit)
        {
            // 光线碰到了介质的边界
            hitRay.origin = interaction.point + hitRay.dir * MathConstant::FLOAT_SMALL_NUMBER;
            // 切换介质状态
            if (hitRay.medium)
                hitRay.medium = nullptr;
            else
                hitRay.medium = interaction.medium;
            
            // 从边界继续追踪，不增加深度
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

    float sampleLightPdf;
    Vector3 lightSurfacePoint = lights.at(lightIndex)->sample(pos, sampleLightPdf);
    Vector3 lightDir = lightSurfacePoint - pos;
    lightDir.normalize();

    // 加上一个小的偏移以避免自相交
    Ray sampleLightRay(pos + lightDir * 0.001f, lightDir);
    sampleRay = sampleLightRay;

    // 获取光源颜色，这个函数内部应该处理可见性测试和透射率
    Color lightColor = pool->getColorFromLight(sampleLightRay, lightIndex);

    if (lightColor.isBlack()){
        return Color::COLOR_BLACK;
    }

    float absDot = std::abs(normal.dot(lightDir));

    // 对于体积内的散射点，几何项没有法线，所以 absDot 应该被吸收到相函数中。
    // 对于各向同性相函数，这里可以认为是1。
    if (isVolumetricPoint)
        absDot = 1.0f;
    
    if(sampleLightPdf < MathConstant::FLOAT_SMALL_NUMBER || lightPickPdf < MathConstant::FLOAT_SMALL_NUMBER){
        return Color::COLOR_BLACK;
    }

    // 返回蒙特卡洛估计量的一部分: L_e * G * Tr / pdf_light
    return lightColor * (absDot / (sampleLightPdf * lightPickPdf));
}

Ray PathIntegrator::genNextRay(const Vector3 &pos, const Vector3 &normal, const Vector3 &reflect) const
{
    // 根据反射方向和法线方向决定偏移方向，避免自相交
    float sign = (normal.dot(reflect) > 0) ? 1.0f : -1.0f;
    Vector3 origin = pos + sign * normal * 0.001f;
    return Ray(origin, reflect);
}