#include "hitterInterface.h"

void HitterInterface::init(const std::vector<Geometry *> &objects, const Light *light)
{
    m_objects = objects;
    m_pLight = light;
}

bool HitterInterface::hitSceneWithLight(const Ray &ray, HitRecord &record, bool &out_isLightHit) const
{
    return false;
}

Color HitterInterface::getColorFromLight(const Ray &ray) const
{
    return Color();
}

bool HitterInterface::hitGeometryObjectOnly(const Ray &ray, HitRecord &record) const
{
    return false;
}