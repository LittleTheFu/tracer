#ifndef _HITTER_H_
#define _HITTER_H_

#include "ray.h"
#include "hitrecord.h"
#include "color.h"
#include <vector>
#include "geometry.h"
#include "hitterInterface.h"

class Hitter : public HitterInterface
{
public:
    virtual bool hitSceneWithLight(
        const std::vector<Geometry *> objects,
        const Light *light,
        const Ray &ray,
        HitRecord &record,
        bool &out_isLightHit) const override;

    virtual Color getColorFromLight(const std::vector<Geometry *> objects,
                            const Light *light,
                            const Ray &ray) const override;

    virtual bool hitGeometryObjectOnly(const std::vector<Geometry *> objects,
                           const Ray &ray,
                           HitRecord &record) const override;

private:
    bool hitLightOnly(const Ray &ray,
                      const Light *pLight,
                      float &t,
                      Vector3 &normal,
                      float &dot) const;
};

#endif