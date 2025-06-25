#include "medium.h"
#include "mathConstantDef.h"
#include <cmath>
#include "mathUtility.h"
#include "mediumInteraction.h"
#include <cassert>

Medium::Medium(float sigma_a, float sigma_s)
    : sigma_a(sigma_a),
      sigma_s(sigma_s),
      sigma_t(sigma_a + sigma_s)
{
    factor_ = 3.0f;
}

float Medium::transmittance(const Ray& ray, float tMax) const
{
    float opticalDepth = 0.0f;
    float stepSize = 0.1f;
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

MediumEventType Medium::sample(const Ray& ray, float tMax, MediumInteraction &interaction)
{
    // float sigma_t_majorant = getSigmaT(ray.origin);
    float sigma_t_majorant = 1.0;

    float current_t = 0.2f;
    while (true)
    {
        float rand_val = MathUtility::genRandomDecimal();
        float sampled_delta_t = -std::log(1.0f - rand_val) / sigma_t_majorant;
        
        current_t += sampled_delta_t;

        if (current_t >= tMax)
        {
            interaction.t = tMax;
            return MediumEventType::Transmit;
        }

        Vector3 pos = ray.getPosition(current_t);
        if( std::isnan(pos.x) || std::isnan(pos.y) || std::isnan(pos.z))
        {
            int a = 3;
        }

        float real_sigma_t = getSigmaT(pos);

        if (MathUtility::genRandomDecimal() < (real_sigma_t / sigma_t_majorant))
        {
            interaction.t = current_t;
            interaction.point = pos;
            interaction.wo = -ray.dir;
            interaction.medium = shared_from_this();

            float albedo = getSigmaS(pos) / real_sigma_t;
            assert(!std::isnan(albedo));
            if (MathUtility::genRandomDecimal() < albedo)
            {
                return MediumEventType::Scatter;
            }
            else
            {
                return MediumEventType::Absorb;
            }
        }
    }

    return MediumEventType::Absorb;
}

float Medium::getSigmaS(const Vector3 &worldPos) const
{
    // float noise = perlinNoise_.get(worldPos * factor_);
    return sigma_s;
}

float Medium::getSigmaA(const Vector3 &worldPos) const
{
    // float noise = perlinNoise_.get(worldPos * factor_);
    // noise = noise * 0.5 + 0.5;
    // return sigma_a + noise * 0.05f;
    float noise = vox_.get(worldPos.x, worldPos.y, worldPos.z);
    // noise = noise * 0.5 + 0.5;
    if(noise > 0.2)
    {
        int a = 3;
    }
    return sigma_a + noise * 0.4;
}

float Medium::getSigmaT(const Vector3 &worldPos) const
{
    float t = getSigmaA(worldPos) + getSigmaS(worldPos);
    assert(!std::isnan(t));
    
    return t;
}
