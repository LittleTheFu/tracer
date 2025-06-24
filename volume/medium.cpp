#include "medium.h"
#include "mathConstantDef.h"
#include <cmath>
#include "mathUtility.h"
#include "mediumInteraction.h"
#include <cassert>

// 注意：你需要在一个共享的头文件（例如 medium.h）中定义这个枚举，
// 以便 pathIntegrator.cpp 和 medium.cpp 都能使用它。
/*

*/

Medium::Medium(float sigma_a, float sigma_s)
    : sigma_a(sigma_a),
      sigma_s(sigma_s),
      sigma_t(sigma_a + sigma_s)
{
    factor_ = 1.0f;
}

// 这个函数保持不变。它对于计算阴影光线（来自NEE）的透射率是正确且必要的。
float Medium::transmittance(const Ray& ray, float tMax) const
{
    // 对于非均匀介质，使用Ray Marching是正确的。
    // 如果你的介质是均匀的，可以简化为：return std::exp(-getSigmaT(ray.origin) * tMax);
    float opticalDepth = 0.0f;
    float stepSize = 0.1f; // 根据精度要求调整步长
    float t = 0;

    while(t < tMax)
    {
        float currentStep = std::min(stepSize, tMax - t);
        Vector3 currentPos = ray.getPosition(t + currentStep * 0.5f);
        opticalDepth += getSigmaT(currentPos) * currentStep;
        t += currentStep;
    }

    return std::exp(-opticalDepth);
}

// **[核心修正]** 重写 sample 函数以实现真正的 Delta Tracking 逻辑
// 函数职责：模拟光子在介质中的随机游走，并返回最终发生的事件。
MediumEventType Medium::sample(const Ray& ray, float tMax, MediumInteraction &interaction)
{
    // 1. 获取一个 majorant extinction coefficient (控制虚拟介质的密度)
    // 对于均匀介质，它就是 sigma_t。
    // 对于非均匀介质，你需要找到该介质中 sigma_t 的最大值。
    float sigma_t_majorant = getSigmaT(ray.origin); // 假设是均匀介质

    float current_t = 0.0f;
    while (true)
    {
        // 2. 在虚拟的 majorant 介质中采样一个随机距离
        // 使用逆变换法从指数分布中采样
        float rand_val = MathUtility::genRandomDecimal(); // 应返回 [0, 1)
        float sampled_delta_t = -std::log(1.0f - rand_val) / sigma_t_majorant;
        
        current_t += sampled_delta_t;

        // 3. 检查是否超出了到下一个表面的距离
        if (current_t >= tMax)
        {
            interaction.t = tMax;
            return MediumEventType::Transmit; // 事件：光线成功穿透
        }

        Vector3 pos = ray.getPosition(current_t);
        float real_sigma_t = getSigmaT(pos);

        // 4. "俄罗斯轮盘赌"：判断是真实碰撞还是虚拟碰撞
        if (MathUtility::genRandomDecimal() < (real_sigma_t / sigma_t_majorant))
        {
            // 发生了真实碰撞 (Real Collision)!
            interaction.t = current_t;
            interaction.point = pos;
            interaction.wo = -ray.dir;
            interaction.medium = shared_from_this();

            // 5. 判断真实碰撞是散射还是吸收
            float albedo = getSigmaS(pos) / real_sigma_t;
            if (MathUtility::genRandomDecimal() < albedo)
            {
                return MediumEventType::Scatter; // 事件：散射
            }
            else
            {
                return MediumEventType::Absorb;  // 事件：吸收
            }
        }
        // else: 发生了虚拟碰撞 (Null Collision)。
        // 我们什么都不做，让光线继续前进，这隐式地处理了透射率。
        // 循环将从当前点继续。
    }

    assert(false && "Control should not escape the Delta Tracking loop!");
    
    // 在Release模式下，为了安全，返回一个确定的值。
    // Absorb 是一个安全的选择，因为它会终止路径，避免产生无限循环或奇怪的颜色。
    return MediumEventType::Absorb;
}

float Medium::getSigmaS(const Vector3 &worldPos) const
{
    // float noise = perlinNoise_.get(worldPos * factor_);
    // return sigma_s * (1 + noise);
    return sigma_s;
}

float Medium::getSigmaA(const Vector3 &worldPos) const
{
    return sigma_a;
}

float Medium::getSigmaT(const Vector3 &worldPos) const
{
    return getSigmaA(worldPos) + getSigmaS(worldPos);
}