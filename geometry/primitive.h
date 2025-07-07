#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include "ray.h"
#include "interaction.h"
#include "material.h"
#include "geometry.h"

class Primitive
{
public:
    Primitive() = default;
    virtual ~Primitive() = default;

    virtual bool intersect(const Ray &ray, Interaction &interaction) const = 0;

    virtual std::shared_ptr<Material> getMaterial() const = 0;
    virtual std::shared_ptr<Geometry> getGeometry() const = 0;

    bool isEmitting() const;
};

#endif