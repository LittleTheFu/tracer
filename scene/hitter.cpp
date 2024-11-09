#include "hitter.h"
#include "mathConstantDef.h"

bool Hitter::hitSceneWithLight(const Ray &ray, HitRecord &record, bool &out_isLightHit) const
{
    out_isLightHit = false;

    bool hit = hitGeometryObjectOnly(ray, record);
    float tMin = record.t;

    float t;
    Vector3 normal;
    float dotLight;
    bool isLightHit = hitLightOnly(ray, t, normal, dotLight);
    if (t < tMin)
    {
        out_isLightHit = true;
        hit = true;

        record.dotLight = dotLight;
    }

    return hit;
}

Color Hitter::getColorFromLight(const Ray &ray) const
{
    // if(m_pLight->isIn(ray.origin))
    // {
    //     return Color::COLOR_WHITE;
    // }

    float t;
    Vector3 normal;
    float dot;

    if (!hitLightOnly(ray, t, normal, dot))
    {
        return Color::COLOR_BLACK;
    }

    Color color = Color::COLOR_WHITE;

    HitRecord record;
    if (!hitGeometryObjectOnly(ray, record))
    {
        return color * dot;
    }

    if (t < record.t)
    {
        return color * dot;
    }

    return Color::COLOR_BLACK;
}

bool Hitter::hitGeometryObjectOnly(const Ray &ray, HitRecord &record) const
{
    bool hit = false;
    float tMin = MathConstant::FLOAT_MAX;

    for (std::vector<Geometry *>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
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

bool Hitter::hitLightOnly(const Ray &ray, float &t, Vector3 &normal, float &dot) const
{
    bool hit = m_pLight->hit(ray, t, normal, dot);
    return hit;
}