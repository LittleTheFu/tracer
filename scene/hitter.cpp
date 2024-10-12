#include "hitter.h"
#include "common.h"

bool Hitter::hitScene(const std::vector<Geometry *> objects,
                      const Ray &ray,
                      HitRecord &record) const
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

bool Hitter::hitSceneWithLight(
    const std::vector<Geometry *> objects,
    const Light *light,
    const Ray &ray,
    HitRecord &record,
    bool &out_isLightHit) const
{
    out_isLightHit = false;

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

    float t;
    Vector3 normal;
    float dotLight;
    bool isLightHit = light->hit(ray, t, normal, dotLight);
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
    if (!light->hit(ray, t, normal, dot))
    {
        // m_pLight->hit(ray, t, normal, dot);
        return Color::COLOR_BLACK;
    }

    Color color = Color::COLOR_WHITE;

    HitRecord record;
    if (!hitScene(objects, ray, record))
    {
        return color * dot;
    }

    if (t < record.t)
    {
        return color * dot;
    }

    return Color::COLOR_BLACK;
}
