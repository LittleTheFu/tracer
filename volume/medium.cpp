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
}

float Medium::transmittance(float distance) const
{
    if (sigma_t < 0.00001f)
    {
        return 1.0f;
    }

    float exponent = -sigma_t * distance;
    return std::exp(exponent);
}

float Medium::sample(const Ray& ray, float tMax, MediumInteraction &interaction)
{
    float pdf = 0;
    float t = MathUtility::sampleExponential(sigma_t, pdf);

    if(t <= tMax)
    {
        interaction.point = ray.getPosition(t);
        interaction.wo = -ray.dir;
        interaction.medium = shared_from_this();

        return pdf;
    }

    interaction.medium = nullptr;
    return 0;
}
