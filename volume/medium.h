#ifndef MEDIUM_H
#define MEDIUM_H

#include "ray.h"
#include <memory>
#include "perlinNoise.h"
// #include "mediumInteraction.h"

class MediumInteraction;
class Ray;

class Medium : public std::enable_shared_from_this<Medium>
{
public:
    Medium(float sigma_a, float sigma_s);

    float transmittance(const Ray& ray, float tMax) const;
    float sample(const Ray& ray, float tMax, MediumInteraction &interaction);

    float getSigmaS(const Vector3& worldPos) const;
    float getSigmaA(const Vector3& worldPos) const;
    float getSigmaT(const Vector3& worldPos) const;

public:
    float sigma_a;
    float sigma_s;
    float sigma_t;

    float factor_;

private:
    PerlinNoise perlinNoise_;
};

#endif