#ifndef _RANDOM_TRACER_H_
#define _RANDOM_TRACER_H_

#include "tracer.h"

class RandomTracer : public Tracer
{
public:
    virtual Color trace(std::shared_ptr<const ObjectPool> pool,
                        Ray &ray,
                        int bounceNum,
                        const HitRecord &currentState) const;
};

#endif