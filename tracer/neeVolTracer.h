#ifndef _NEE_VOL_TRACER_H_
#define _NEE_VOL_TRACER_H_

#include "tracer.h"
#include "objectpool.h"
#include "ray.h"
#include "color.h"
#include "russianRouletter.h"
#include <memory>

class NeeVolTracer : public Tracer
{
public:
    NeeVolTracer(int depth = 20);
    Color trace(std::shared_ptr<const ObjectPool> pool, Ray &ray) const override;

private:
    Color sampleLightFromDeltaMaterial(std::shared_ptr<const ObjectPool> pool,
                                       const Vector3 &pos,
                                       const Vector3 &dir) const;

    Color sampleLightFromNormalMaterial(std::shared_ptr<const ObjectPool> pool,
                                       const Vector3 &pos,
                                       const Vector3 &normal,
                                       Ray &sampleRay) const;

    Ray genNextRay(const HitRecord &record) const;

private:
    int m_depth;
    RussianRouletter m_rouletter;
};

#endif