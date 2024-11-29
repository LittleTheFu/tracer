#ifndef _TRACER_H_
#define _TRACER_H_

#include "objectpool.h"
#include "ray.h"
#include "hitrecord.h"
#include "color.h"
#include <memory>

class Tracer
{
public:
    virtual Color trace(std::shared_ptr<const ObjectPool> pool,
                        Ray &ray,
                        int bounceNum,
                        const HitRecord &currentState) const;

    virtual Color traceFirstBounce(std::shared_ptr<const ObjectPool> pool, Ray &ray) const;
};

#endif