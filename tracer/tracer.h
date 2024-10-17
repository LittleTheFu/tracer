#ifndef _TRACER_H_
#define _TRACER_H_

#include "objectpool.h"
#include "ray.h"
#include "hitrecord.h"
#include "color.h"

class Tracer
{
public:
    virtual Color trace(const ObjectPool *pool,
                        Ray &ray,
                        int bounceNum,
                        const HitRecord &currentState) const;
};

#endif