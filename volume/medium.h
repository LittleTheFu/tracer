#ifndef MEDIUM_H
#define MEDIUM_H

#include "ray.h"
#include <memory>
#include "perlinNoise.h"
#include "mediumEvent.h"
#include "vox.h"

class MediumInteraction;
class Ray;



class Medium : public std::enable_shared_from_this<Medium>
{
public:
    Medium();
    Medium(float sigma_a, float sigma_s, float eta = 1.0f);

    float transmittance(const Ray& ray, float tMax) const;
    MediumEventType sample(const Ray& ray, float tMax, MediumInteraction &interaction);

    float getSigmaS(const Vector3& worldPos) const;
    float getSigmaA(const Vector3& worldPos) const;
    float getSigmaT(const Vector3& worldPos) const;

public:
    float sigma_a;
    float sigma_s;
    float sigma_t;

    float factor_;

    float eta_;

private:
    //for test
    PerlinNoise perlinNoise_;

    //this should be passed as a parameter,I'will come back here later.
    //right now is in devlopment.
    Vox vox_;
};

#endif