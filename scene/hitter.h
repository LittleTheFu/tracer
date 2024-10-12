#ifndef _HITTER_H_
#define _HITTER_H_

#include "ray.h"
#include "hitrecord.h"
#include "color.h"
#include <vector>
#include "geometry.h"

class Hitter
{
public:
    bool hitSceneWithLight(
        const std::vector<Geometry *> objects,
        const Light *light,
        const Ray &ray,
        HitRecord &record,
        bool &out_isLightHit) const;

    Color getColorFromLight(const std::vector<Geometry *> objects,
                            const Light *light,
                            const Ray &ray) const;

    bool hitGeometryObjectOnly(const std::vector<Geometry *> objects,
                           const Ray &ray,
                           HitRecord &record) const;

    bool hitLightOnly(const Ray &ray,
                      const Light *pLight,
                      float &t,
                      Vector3 &normal,
                      float &dot) const;
};

#endif