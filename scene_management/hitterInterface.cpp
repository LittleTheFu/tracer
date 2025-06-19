#include "hitterInterface.h"

void HitterInterface::init(std::vector<std::shared_ptr<AreaLight>> lights,
                           const std::vector<std::shared_ptr<Primitive>> &primitives)
{
    primitives_ = primitives;
    lights_ = lights;
}

Color HitterInterface::getColorFromLight(const Ray &ray, int index) const
{
    return Color();
}

bool HitterInterface::hitGeometryObjectOnly(const Ray &ray, Interaction &interaction, std::shared_ptr<Primitive> skipPrimitive) const
{
    return false;
}