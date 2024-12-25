#ifndef _HITTER_INTERFACE_H_
#define _HITTER_INTERFACE_H_

#include <vector>
#include "geometry.h"
#include "light.h"
#include "ray.h"
#include "hitrecord.h"
#include <memory>

class HitterInterface
{
public:
    virtual void init(const std::vector<std::shared_ptr<Geometry>> &objects, std::shared_ptr<const Light> light);
    virtual Color getColorFromLight(const Ray &ray) const;

    virtual bool hitGeometryObjectOnly(
        const Ray &ray,
        HitRecord &record, 
        bool skipVolume = false) const;

protected:
    std::vector<std::shared_ptr<Geometry>> m_objects;
    std::shared_ptr<const Light> m_pLight;
};

#endif