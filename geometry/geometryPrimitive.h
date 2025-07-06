#ifndef GEOMETRY_PRIMITIVE_H_
#define GEOMETRY_PRIMITIVE_H_

#include "primitive.h"

class MediumBoundary;

class GeometryPrimitive : public Primitive
{
public:
    GeometryPrimitive(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);
    ~GeometryPrimitive() = default;

    virtual bool intersect(const Ray &ray, Interaction &interaction) const override;

    virtual std::shared_ptr<Material> getMaterial() const override;
    virtual std::shared_ptr<Geometry> getGeometry() const override;

private:
    std::shared_ptr<Geometry> geometry_;
    std::shared_ptr<Material> material_;

    //this should be moved to geometry primitive class
    std::shared_ptr<MediumBoundary> mediumBoundary_;
};

#endif