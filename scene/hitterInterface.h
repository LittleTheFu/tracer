#ifndef _HITTER_INTERFACE_H_
#define _HITTER_INTERFACE_H_

#include <memory>
#include <vector>

#include "geometry.h"
#include "light.h"
#include "ray.h"
#include "interaction.h"
#include "primitive.h"


class HitterInterface
{
public:
    virtual void init(std::shared_ptr<const Light> light,
                      const std::vector<std::shared_ptr<Primitive>> &primitives);
    virtual Color getColorFromLight(const Ray &ray) const;

    virtual bool hitGeometryObjectOnly(const Ray &ray, Interaction &interaction) const;

protected:
    std::vector<std::shared_ptr<Geometry>> m_objects;
    std::shared_ptr<const Light> m_pLight;

    std::vector<std::shared_ptr<Primitive>> primitives_;
};

#endif