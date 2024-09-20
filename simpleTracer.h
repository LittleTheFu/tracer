#ifndef _SIMPLE_TRACER_H_
#define _SIMPLE_TRACER_H_

#include "tracer.h"

class SimpleTracer : public Tracer
{
public:
    virtual Color trace(const ObjectPool *pool, Ray &ray, int bounceNum, const HitRecord &currentState) const;
};

#endif