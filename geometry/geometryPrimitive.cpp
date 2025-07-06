#include "geometryPrimitive.h"
#include "mediumManager.h"
#include "mediumBoundary.h"
#include <cassert>

GeometryPrimitive::GeometryPrimitive(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material, std::shared_ptr<MediumBoundary> mediumBoundary)
    : geometry_(geometry), material_(material), mediumBoundary_(mediumBoundary)
{
    if(mediumBoundary_ == nullptr)
    {
        std::shared_ptr<Medium> vacuum = MediumManager::getInstance().getMedium(MediumType::VACUUM);
        mediumBoundary_ = std::make_shared<MediumBoundary>();
        mediumBoundary_->mediumOutside_ = vacuum;
        mediumBoundary_->mediumInside_ = vacuum;
    }
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

std::shared_ptr<MediumBoundary> GeometryPrimitive::getMediumBoundary() const
{
    return mediumBoundary_;
}
