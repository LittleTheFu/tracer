#include "hitterInterface.h"

void HitterInterface::init(const std::vector<std::shared_ptr<Geometry>> &objects, std::shared_ptr<const Light> light)
{
    m_objects = objects;
    m_pLight = light;
}

Color HitterInterface::getColorFromLight(const Ray &ray) const
{
    return Color();
}

bool HitterInterface::hitGeometryObjectOnly(const Ray &ray, HitRecord &record) const
{
    return false;
}