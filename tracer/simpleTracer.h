#ifndef _SIMPLE_TRACER_H_
#define _SIMPLE_TRACER_H_

#include "tracer.h"

class SimpleTracer : public Tracer
{
public:
    virtual Color trace(std::shared_ptr<const ObjectPool> pool,
                        Ray &ray,
                        int bounceNum,
                        const HitRecord &currentState) const;

private:
    Color HandleLastBounce(std::shared_ptr<const ObjectPool> pool,
                           const Ray &ray,
                           const HitRecord &currentState) const;

    void prepareSampleLight(std::shared_ptr<const ObjectPool> pool,
                            Ray &newRay,
                            HitRecord &record) const;
};

#endif