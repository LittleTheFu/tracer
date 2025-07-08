#include "areaLight.h"
#include <cassert>
#include "ball.h"
#include "tri.h"
#include "geometryPrimitive.h"
#include "material.h"

AreaLight::AreaLight(std::shared_ptr<GeometryPrimitive> geometryPrimitive)
    : geometryPrimitive_(geometryPrimitive)
{
    assert(geometryPrimitive_ != nullptr);
    assert(geometryPrimitive_->getMaterial() != nullptr);
    assert(geometryPrimitive_->isEmitting());

    color_ = geometryPrimitive_->getMaterial()->getEmittedRadiance();
}

Color AreaLight::getColor() const
{
    return color_;
}

void AreaLight::setColor(const Color &finalColor)
{
    color_ = finalColor;
}

void AreaLight::applyIntensityScale(float scale)
{
    color_ *= scale;
}


void AreaLight::applyTransform(const Transform &t)
{
    geometryPrimitive_->getGeometry()->applyTransform(t);
}

//no more light balls
Vector3 AreaLight::sample(const Vector3 &thatPoint, float &pdf, Vector3 &normal) const
{
    //quick and dirty,we will reconsider it later...
    std::shared_ptr<Geometry> geometry = geometryPrimitive_->getGeometry();
    assert(geometry != nullptr);

    std::shared_ptr<Tri> tri = std::dynamic_pointer_cast<Tri>(geometry);
    assert(tri != nullptr);

    return tri->sampleFromPoint(thatPoint, pdf, normal);

    // std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(geometry);
    // assert(ball != nullptr);

    // return ball->sampleFromPoint(thatPoint, pdf);
}

std::shared_ptr<GeometryPrimitive> AreaLight::getGeometryPrimitive() const
{
    return geometryPrimitive_;
}