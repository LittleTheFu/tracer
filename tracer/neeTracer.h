#ifndef _NEE_TRACER_H_
#define _NEE_TRACER_H_

#include "tracer.h"
#include "objectPool.h"
#include "ray.h"
#include "color.h"
#include <memory>

class  NeeTracer : public Tracer
{
public:
    NeeTracer(int depth = 10);
	Color trace(std::shared_ptr<const ObjectPool> pool,Ray &ray) const override;

private:
    int m_depth;
};

#endif