#ifndef _NEE_TRACER_H_
#define _NEE_TRACER_H_

#include <memory>

#include "color.h"
#include "objectpool.h"
#include "ray.h"
#include "russianRoulette.h"
#include "tracer.h"

class NeeTracer : public Tracer
{
public:
    NeeTracer(int depth = 20);
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
    void getLocalWoWi(const HitRecord &record,
                         const Vector3 &worldWo,
                         const Vector3 &worldWi,
                         Vector3 &wo,
                         Vector3 &wi) const;

private:
    int m_depth;
    RussianRoulette m_rouletter;
};

#endif