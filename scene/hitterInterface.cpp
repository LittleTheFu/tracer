#include "hitterInterface.h"

void HitterInterface::init(std::shared_ptr<const AreaLight> light,
                           const std::vector<std::shared_ptr<Primitive>> &primitives)
{
    primitives_ = primitives;
    light_ = light;
}

Color HitterInterface::getColorFromLight(const Ray &ray) const
{
    return Color();
}

bool HitterInterface::hitGeometryObjectOnly(const Ray &ray, Interaction &interaction) const
{
    return false;
}