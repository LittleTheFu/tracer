#include "hitter.h"
#include "mathConstantDef.h"

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

    Color color = m_pLight->getColor();

    HitRecord record;
    if (!hitGeometryObjectOnly(ray, record))
    {
        // return color * dot;
        return color;
    }

    if(record.t < 0.001f)
    {
        return color;
    }

    if (t < record.t)
    {
        // return color * dot;
        return color;
    }

    return Color::COLOR_BLACK;
}

bool Hitter::hitGeometryObjectOnly(const Ray &ray, HitRecord &record) const
{
    bool hit = false;
    float tMin = MathConstant::FLOAT_MAX;

    for (auto it = m_objects.begin(); it != m_objects.end(); it++)
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