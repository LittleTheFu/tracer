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
    virtual void init(const std::vector<Geometry *> &objects, const Light *light);
    virtual Color getColorFromLight(const Ray &ray) const;

    virtual bool hitGeometryObjectOnly(
        const Ray &ray,
        HitRecord &record) const;

protected:
    std::vector<Geometry *> m_objects;
    const Light *m_pLight;
};

#endif