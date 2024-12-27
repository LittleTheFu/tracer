#ifndef _NEE_VOL_TRACER_H_
#define _NEE_VOL_TRACER_H_

#include "tracer.h"
#include "objectpool.h"
#include "ray.h"
#include "color.h"
#include "RussianRoulette.h"
#include "vox.h"
#include <memory>

class NeeVolTracer : public Tracer
{
public:
    NeeVolTracer(int depth = 9);
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

    // should be renamed later
    Color evalVaccum(std::shared_ptr<const ObjectPool> pool,
                      const HitRecord &record,
                      Ray &hitRay,
                      Color &beta,
                      Color &color,
                      bool &isVacuum,
                      float &pdf,
                      bool &isPassingVolume) const;

    void evalVolume(std::shared_ptr<const ObjectPool> pool,
                  Ray &hitRay,
                  bool &isVacuum,
                  int &depth,
                  Color &beta,
                  float &pdf,
                  Color &color,
                  bool &isAbsorbed,
                  bool &isPassingVolume) const;

private:
    int m_depth;
    RussianRoulette m_rouletter;

    Vox m_vox;
    int n_trave_factor;
    bool m_isPassingVolumeBoundery;
};

#endif