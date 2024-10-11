#ifndef _SIMPLE_TRACER_H_
#define _SIMPLE_TRACER_H_

#include "tracer.h"

class SimpleTracer : public Tracer
{
public:
    virtual Color trace(const ObjectPool *pool,
                        const BVH *bvh,
                        Ray &ray,
                        int bounceNum,
                        const HitRecord &currentState) const;

private:
    Color HandleLastBounce(const ObjectPool *pool,
                           const BVH *bvh,
                           const Ray &ray,
                           const HitRecord &currentState) const;

    void prepareSampleLight(const ObjectPool *pool,
                            const BVH *bvh,
                            Ray &newRay,
                            HitRecord &record) const;
};

#endif