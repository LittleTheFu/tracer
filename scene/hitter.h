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
    bool hitScene(const std::vector<Geometry *> objects,
                  const Ray &ray,
                  HitRecord &record) const;

    bool hitSceneWithLight(
        const std::vector<Geometry *> objects,
        const Light *light,
        const Ray &ray,
        HitRecord &record,
        bool &out_isLightHit) const;

    Color getColorFromLight(const std::vector<Geometry *> objects,
                            const Light *light,
                            const Ray &ray) const;
};

#endif