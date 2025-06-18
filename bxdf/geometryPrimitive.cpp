#include "geometryPrimitive.h"
#include <cassert>

GeometryPrimitive::GeometryPrimitive(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material)
    : geometry_(geometry), material_(material)
{
}

bool GeometryPrimitive::intersect(const Ray &ray, Interaction &interaction) const
{
    assert(geometry_ != nullptr);

    if (geometry_->hit(ray, interaction))
    {
        return true;
    }

    return false;
}

std::shared_ptr<Material> GeometryPrimitive::getMaterial() const
{
    return material_;
}

std::shared_ptr<Geometry> GeometryPrimitive::getGeometry() const
{
    return geometry_;
}
