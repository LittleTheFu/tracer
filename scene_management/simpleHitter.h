#ifndef _SIMPLE_HITTER_H_
#define _SIMPLE_HITTER_H_

#include <vector>

#include "color.h"
#include "geometry.h"
#include "hitterInterface.h"
#include "ray.h"

class SimperHitter : public HitterInterface
{
public:
    virtual Color getColorFromLight(const Ray &ray, int index) const override;
    virtual bool hitGeometryObjectOnly(const Ray &ray, Interaction &interaction, std::shared_ptr<Primitive> skipPrimitive) const override;


private:
    // bool hitLightOnly(const Ray &ray, float &t, Vector3 &normal, float &dot) const;
};

#endif