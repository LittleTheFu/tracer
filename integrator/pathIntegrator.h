#ifndef _PATH_INTEGRATOR_H_
#define _PATH_INTEGRATOR_H_

#include "integrator.h"

class PathIntegrator : public Integrator
{
public:
    PathIntegrator(int depth);
    virtual Color Li(const Ray &ray, std::shared_ptr<const ObjectPool> pool) const override;

private:
    // Color sampleLightFromDeltaMaterial(std::shared_ptr<const ObjectPool> pool,
    //                                    const Vector3 &pos,
    //                                    const Vector3 &dir) const;

    Color sampleLightFromNormalMaterial(std::shared_ptr<const ObjectPool> pool,
                                        const Vector3 &pos,
                                        const Vector3 &normal,
                                        Ray &sampleRay,
                                        bool isVolumetricPoint = false) const;

    Ray genNextRay(const Vector3 &pos,
                   const Vector3 &normal,
                   const Vector3 &reflect) const;

private:
    int depth_ = 5;
};

#endif