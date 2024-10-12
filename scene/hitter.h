#ifndef _HITTER_H_
#define _HITTER_H_

#include "ray.h"
#include "hitrecord.h"
#include "color.h"

class Hitter
{
public:
    bool hitScene(const Ray &ray, HitRecord &record) const;
    bool hitSceneWithLight(const Ray &ray, HitRecord &record, bool &out_isLightHit) const;

    Color getColorFromLight(const Ray &ray) const;
};

#endif