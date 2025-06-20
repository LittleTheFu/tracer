#include "medium.h"
#include "mathConstantDef.h"
#include <cmath>
#include "mathUtility.h"


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

float Medium::sample(const Ray& ray, float tMax, Interaction &interaction)
{
    float pdf = 0;
    float t = MathUtility::sampleExponential(sigma_t, pdf);

    if(t <= tMax)
    {
        interaction.point = ray.getPosition(t);
        interaction.wo = -ray.dir;
        interaction.medium = std::shared_ptr<Medium>(this);

        return pdf;
    }

    interaction.medium = nullptr;
    return 0;
}
