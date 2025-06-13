#include "areaLight.h"
#include <cassert>
#include <ball.h>

AreaLight::AreaLight(std::shared_ptr<GeometryPrimitive> geometryPrimitive)
    : geometryPrimitive_(geometryPrimitive)
{
    assert(geometryPrimitive_ != nullptr);
    assert(geometryPrimitive_->getMaterial() != nullptr);
    assert(geometryPrimitive_->isEmitting());

    color_ = geometryPrimitive_->getMaterial()->getEmittedRadiance();
    intensity_ = 40.0f;
}

Color AreaLight::getColor() const
{
    return color_;
}

void AreaLight::setIntensity(float intensity)
{
    intensity_ = intensity;
}

float AreaLight::getIntensity() const
{
    return intensity_;
}

void AreaLight::applyTransform(const Transform &t)
{
    geometryPrimitive_->getGeometry()->applyTransform(t);
}

Vector3 AreaLight::sample(const Vector3 &thatPoint, float &pdf) const
{
    //quick and dirty,we will reconsider it later...
    std::shared_ptr<Geometry> geometry = geometryPrimitive_->getGeometry();
    assert(geometry != nullptr);

    std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(geometry);
    assert(ball != nullptr);

    return ball->sampleFromPoint(thatPoint, pdf);
}

std::shared_ptr<GeometryPrimitive> AreaLight::getGeometryPrimitive() const
{
    return geometryPrimitive_;
}
