#ifndef _HITTER_INTERFACE_H_
#define _HITTER_INTERFACE_H_

#include <memory>
#include <vector>

#include "geometry.h"
#include "ray.h"
#include "interaction.h"
#include "primitive.h"
#include "areaLight.h"

class HitterInterface
{
public:
    virtual void init(std::vector<std::shared_ptr<AreaLight>> lights,
                      const std::vector<std::shared_ptr<Primitive>> &primitives);
    virtual Color getColorFromLight(const Ray &ray, int index) const;

    //dirty: light ptr
    virtual bool hitGeometryObjectOnly(const Ray &ray, Interaction &interaction, std::shared_ptr<Primitive> skipPrimitive = nullptr) const;

protected:

    std::vector<std::shared_ptr<Primitive>> primitives_;
    std::vector<std::shared_ptr<AreaLight>> lights_;
};

#endif