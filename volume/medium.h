#ifndef MEDIUM_H
#define MEDIUM_H

#include "ray.h"
#include <memory>
// #include "mediumInteraction.h"

class MediumInteraction;

class Medium : public std::enable_shared_from_this<Medium>

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