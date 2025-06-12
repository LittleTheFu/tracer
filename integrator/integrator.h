#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_


#include "color.h"
#include "ray.h"
#include "scene.h"

class Integrator
{
public:
    Integrator( int maxDepth = 5);
    virtual Color Li(const Ray &ray, const Scene &scene) const = 0;

protected:
    int maxDepth_;
};

#endif