#ifndef _VOL_TRACER_H_
#define _VOL_TRACER_H_

#include "tracer.h"

class VolTracer : public Tracer
{
public:
    Color trace(const ObjectPool *pool,
                Ray &ray,
                int bounceNum,
                const HitRecord &currentState) const override;

    Color traceFirstBounce(const ObjectPool *pool, Ray &ray) const override;
};

#endif