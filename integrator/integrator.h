#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

#include "color.h"
#include "ray.h"
#include "scene.h"
#include "objectpool.h"
#include <memory>

class Integrator
{
public:
    Integrator( int maxDepth = 10);
    virtual Color Li(const Ray &ray, std::shared_ptr<const ObjectPool> pool) const = 0;

protected:
    int maxDepth_;
};

#endif