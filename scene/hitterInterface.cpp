#include "hitterInterface.h"

bool HitterInterface::hitSceneWithLight(const std::vector<Geometry *> objects, const Light *light, const Ray &ray, HitRecord &record, bool &out_isLightHit) const
{
    return false;
}

Color HitterInterface::getColorFromLight(const std::vector<Geometry *> objects, const Light *light, const Ray &ray) const
{
    return Color();
}

bool HitterInterface::hitGeometryObjectOnly(const std::vector<Geometry *> objects, const Ray &ray, HitRecord &record) const
{
    return false;
}