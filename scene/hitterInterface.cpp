#include "hitterInterface.h"

void HitterInterface::init(const std::vector<Geometry *> &objects, const Light *light)
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