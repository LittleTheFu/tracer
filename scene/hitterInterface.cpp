#include "hitterInterface.h"

void HitterInterface::init(const std::vector<std::shared_ptr<Geometry>> &objects,
                           std::shared_ptr<const Light> light,
                           const std::vector<std::shared_ptr<Primitive>> &primitives)
{
    m_objects = objects;
    m_pLight = light;

    primitives_ = primitives;
}

Color HitterInterface::getColorFromLight(const Ray &ray) const
{
    return Color();
}

bool HitterInterface::hitGeometryObjectOnly(const Ray &ray, Interaction &interaction) const
{
    return false;
}