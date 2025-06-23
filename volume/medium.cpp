#include "medium.h"
#include "mathConstantDef.h"
#include <cmath>
#include "mathUtility.h"
#include "mediumInteraction.h"

Medium::Medium(float sigma_a, float sigma_s)
    : sigma_a(sigma_a),
      sigma_s(sigma_s),
      sigma_t(sigma_a + sigma_s)
{
    factor_ = 1.0f;
}

float Medium::transmittance(const Ray& ray, float tMax) const
{
    float opticalDepth = 0.0f;
    float stepSize = 0.1f; // 根据精度要求调整步长
    float t = 0;

    while(t < tMax)
    {
        float currentStep = std::min(stepSize, tMax - t); // 确保最后一步不超过 tMax
        Vector3 currentPos = ray.getPosition(t + currentStep * 0.5f); // 在步长中间采样位置

        // 累加真实介质在该位置的消光系数乘以步长
        opticalDepth += getSigmaT(currentPos) * currentStep;

        t += currentStep;
    }

    return std::exp(-opticalDepth);
}


float Medium::sample(const Ray& ray, float tMax, MediumInteraction &interaction)
{
    float temp_pdf_from_exponential = 0; 
    float sigma_t_majorant = 0.35f; // Debug 值，注意确保是实际最大 sigma_t 的上限

    float current_t = 0.0f;
    // **修正 1：引入并初始化累积指数衰减因子**
    float accumulated_majorant_exp_factor = 1.0f; 

    while(current_t <= tMax)
    {
        float sampled_delta_t_majorant = MathUtility::sampleExponential(sigma_t_majorant, temp_pdf_from_exponential);
        
        // **修正 2：更新累积指数衰减因子**
        accumulated_majorant_exp_factor *= std::exp(-sigma_t_majorant * sampled_delta_t_majorant);

        current_t += sampled_delta_t_majorant;

        if(current_t >= tMax)
            break;

        Vector3 pos = ray.getPosition(current_t);
        float real_sigma_t = getSigmaT(pos);
        
        float rnd = MathUtility::genRandomDecimal();
        if (rnd < (real_sigma_t / sigma_t_majorant)) // 发生真实碰撞 (散射或吸收)
        {
            interaction.t = current_t;
            interaction.point = pos;
            interaction.wo = -ray.dir;
            interaction.medium = shared_from_this();

            // **修正 3：判断是散射还是吸收，并返回相应的 PDF**
            float albedo = getSigmaS(pos) / real_sigma_t; // 单次散射反照率

            if (MathUtility::genRandomDecimal() < albedo) // 发生散射
            {
                // 返回完整的散射事件 PDF
                return getSigmaS(pos) * (real_sigma_t / sigma_t_majorant) * accumulated_majorant_exp_factor;
            }
            else // 发生吸收
            {
                // 吸收事件不产生光线贡献，返回 0 PDF
                return 0.0f; 
            }
        }
    }

    interaction.t = tMax;
    interaction.medium = nullptr;

    // **修正 4：光线穿透介质时返回真实的透射率**
    // 假设你的介质最终会是非均匀的，因此使用 transmittance(ray, tMax)
    return transmittance(ray, tMax); 
    // 如果介质始终是均匀的，你现在使用的 std::exp(-sigma_t * tMax) 也可以，但未来会出问题。
}

float Medium::getSigmaS(const Vector3 &worldPos) const
{
    // float noise = perlinNoise_.get(worldPos * factor_);
    
    // return sigma_s * (1 + noise);
    return sigma_s;
}

float Medium::getSigmaA(const Vector3 &worldPos) const
{
    //for debug
    return sigma_a;
}

float Medium::getSigmaT(const Vector3 &worldPos) const
{
    return getSigmaA(worldPos) + getSigmaS(worldPos);
}