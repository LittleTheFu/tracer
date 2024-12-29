#ifndef _TRACER_H_
#define _TRACER_H_

#include <memory>

#include "color.h"
#include "hitrecord.h"
#include "objectpool.h"
#include "ray.h"

class Tracer
{
public:
    virtual Color trace(std::shared_ptr<const ObjectPool> pool,
                        Ray &ray,
                        int bounceNum,
                        const HitRecord &currentState) const;

    virtual Color trace(std::shared_ptr<const ObjectPool> pool,Ray &ray) const;

    virtual Color traceFirstBounce(std::shared_ptr<const ObjectPool> pool, Ray &ray) const;
};

#endif