#include "hitterInterface.h"

void HitterInterface::init(std::vector<std::shared_ptr<AreaLight>> lights,
                           const std::vector<std::shared_ptr<Primitive>> &primitives,
                           std::shared_ptr<SphereVolume> volume)
{
    primitives_ = primitives;
    lights_ = lights;
    volume_ = volume;
}

Color HitterInterface::getColorFromLight(const Ray &ray, int index) const
{
    return Color();
}

bool HitterInterface::hitGeometryObjectOnly(const Ray &ray, Interaction &interaction, std::shared_ptr<Primitive> skipPrimitive) const
{
    return false;
}

bool HitterInterface::isVolumePrimitive(std::shared_ptr<const Primitive> primitive) const
{
    if(volume_ == nullptr)
        return false;

    return (volume_->getGeometry() == primitive->getGeometry());
}