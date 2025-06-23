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
    float pdf = 0;

    //for debug
    float debug_sigma_t_majorant = 0.35;

    float sigma_t_majorant = debug_sigma_t_majorant;
    float current_t = 0.0f;

    while(current_t <= tMax)
    {
        float sampled_delta_t_majorant = MathUtility::sampleExponential(sigma_t_majorant, pdf);
        current_t += sampled_delta_t_majorant;

        if(current_t >= tMax)
            break;

        Vector3 pos = ray.getPosition(current_t);
        float real_sigma_t = getSigmaT(pos);
        
        float rnd = MathUtility::genRandomDecimal();
        if (rnd < (real_sigma_t / sigma_t_majorant))
        {
            interaction.t = current_t;
            interaction.point = pos;
            interaction.wo = -ray.dir;
            interaction.medium = shared_from_this();

            pdf = getSigmaS(pos);
            return pdf;
        }
        
    }

    interaction.t = tMax;
    interaction.medium = nullptr;

    return std::exp(-sigma_t * tMax);
    // return 0;
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