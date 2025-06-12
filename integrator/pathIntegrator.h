#ifndef _PATH_INTEGRATOR_H_
#define _PATH_INTEGRATOR_H_

#include "integrator.h"

class PathIntegrator : public Integrator
{
public:
    virtual Color Li(const Ray &ray, const Scene &scene) const override;
};

#endif