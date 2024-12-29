#include "hitter.h"
#include "mathConstantDef.h"
#include "mathUtility.h"

Color SimperHitter::getColorFromLight(const Ray &ray) const
{
    float t = 0.0f;
    float dot = 1.0f;
    Vector3 normal;

    if (!hitLightOnly(ray, t, normal, dot))
    {
        return Color::COLOR_BLACK;
    }

    Color color = m_pLight->getColor();

    HitRecord record;
    if (!hitGeometryObjectOnly(ray, record, true))
    {
        return color;
    }

    if (t < record.t)
    {
        return color;
    }

    return Color::COLOR_BLACK;
}

bool SimperHitter::hitGeometryObjectOnly(const Ray &ray, HitRecord &record, bool skipVolume) const
{
    bool hit = false;
    float tMin = MathConstant::FLOAT_MAX;

    for (auto it = m_objects.begin(); it != m_objects.end(); it++)
    {
        HitRecord tempRecord;

        if(skipVolume && (*it)->isVolume())
            continue;

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

bool SimperHitter::hitLightOnly(const Ray &ray, float &t, Vector3 &normal, float &dot) const
{
    bool hit = m_pLight->hit(ray, t, normal, dot);
    return hit;
}