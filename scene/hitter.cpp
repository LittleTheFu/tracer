#include "hitter.h"
#include "common.h"

bool Hitter::hitSceneWithLight(
    const std::vector<Geometry *> objects,
    const Light *light,
    const Ray &ray,
    HitRecord &record,
    bool &out_isLightHit) const
{
    out_isLightHit = false;

    bool hit = hitGeometryObject(objects, ray, record);
    float tMin = record.t;

    float t;
    Vector3 normal;
    float dotLight;
    bool isLightHit = hitLightOnly(ray, light, t, normal, dotLight);
    if (t < tMin)
    {
        out_isLightHit = true;
        hit = true;

        record.dotLight = dotLight;
    }

    return hit;
}

Color Hitter::getColorFromLight(
    const std::vector<Geometry *> objects,
    const Light *light,
    const Ray &ray) const
{
    float t;
    Vector3 normal;
    float dot;

    if (!hitLightOnly(ray, light, t, normal, dot))
    {
        return Color::COLOR_BLACK;
    }

    Color color = Color::COLOR_WHITE;

    HitRecord record;
    if (!hitGeometryObject(objects, ray, record))
    {
        return color * dot;
    }

    if (t < record.t)
    {
        return color * dot;
    }

    return Color::COLOR_BLACK;
}

bool Hitter::hitGeometryObject(const std::vector<Geometry *> objects, const Ray &ray, HitRecord &record) const
{
    bool hit = false;
    float tMin = Common::FLOAT_MAX;

    for (std::vector<Geometry *>::const_iterator it = objects.begin(); it != objects.end(); it++)
    {
        HitRecord tempRecord;

        if ((*it)->hit(ray, tempRecord))
        {
            if (tempRecord.t < tMin)
            {
                tMin = tempRecord.t;
                record = tempRecord;
                hit = true;
            }
        }
    }

    return hit;
}

bool Hitter::hitLightOnly(const Ray &ray,
                          const Light *pLight,
                          float &t,
                          Vector3 &normal,
                          float &dot) const
{
    bool hit = pLight->hit(ray, t, normal, dot);
    return hit;
}
