#ifndef MEDIUM_H
#define MEDIUM_H

#include "ray.h"
#include "mediumInteraction.h"

class Medium
{
public:
    Medium(float sigma_a, float sigma_s);

    float transmittance(float distance) const;
    float sample(const Ray& ray, float tMax, MediumInteraction &interaction);

public:
    float sigma_a;
    float sigma_s;
    float sigma_t;
};

#endif