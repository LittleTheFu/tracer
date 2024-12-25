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
    virtual Color getColorFromLight(const Ray &ray) const override;
    virtual bool hitGeometryObjectOnly(const Ray &ray, HitRecord &record, bool skipVolume = false) const override;

private:
    bool hitLightOnly(const Ray &ray, float &t, Vector3 &normal, float &dot) const;
};

#endif