#ifndef _HITTER_INTERFACE_H_
#define _HITTER_INTERFACE_H_

#include <vector>
#include "geometry.h"
#include "light.h"
#include "ray.h"
#include "hitrecord.h"

class HitterInterface
{
public:
    virtual bool hitSceneWithLight(
        const std::vector<Geometry *> objects,
        const Light *light,
        const Ray &ray,
        HitRecord &record,
        bool &out_isLightHit) const;

    virtual Color getColorFromLight(const std::vector<Geometry *> objects,
                            const Light *light,
                            const Ray &ray) const;

    virtual bool hitGeometryObjectOnly(const std::vector<Geometry *> objects,
                               const Ray &ray,
                               HitRecord &record) const;
};

#endif