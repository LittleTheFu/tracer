#include "hitter.h"
#include "common.h"
#include <vector>
#include "geometry.h"

bool Hitter::hitScene(const Ray &ray, HitRecord &record) const
{
    // bool hit = false;
    // float tMin = Common::FLOAT_MAX;

    // for (std::vector<Geometry *>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
    // {
    //     HitRecord tempRecord;

    //     if ((*it)->hit(ray, tempRecord, pLight))
    //     {
    //         if (tempRecord.t < tMin)
    //         {
    //             tMin = tempRecord.t;
    //             record = tempRecord;
    //             hit = true;
    //         }
    //     }
    // }

    // return hit;
    return false;
}

bool Hitter::hitSceneWithLight(const Ray &ray, HitRecord &record, bool &out_isLightHit) const
{
    // out_isLightHit = false;

    // bool hit = false;
    // float tMin = Common::FLOAT_MAX;

    // for (std::vector<Geometry *>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
    // {
    //     HitRecord tempRecord;

    //     if ((*it)->hit(ray, tempRecord, nullptr))
    //     {
    //         if (tempRecord.t < tMin)
    //         {
    //             tMin = tempRecord.t;
    //             record = tempRecord;
    //             hit = true;
    //         }
    //     }
    // }

    // float t;
    // Vector3 normal;
    // float dotLight;
    // bool isLightHit = m_pLight->hit(ray, t, normal, dotLight);
    // if( t < tMin)
    // {
    //     out_isLightHit = true;
    //     hit = true;

    //     record.dotLight = dotLight;
    // }

    // return hit;
    return false;
}

Color Hitter::getColorFromLight(const Ray &ray) const
{
    // float t;
    // Vector3 normal;
    // float dot;
    // if (!m_pLight->hit(ray, t, normal, dot))
    // {
    //     // m_pLight->hit(ray, t, normal, dot);
    //     return Color::COLOR_BLACK;
    // }

    // Color color = Color::COLOR_WHITE;

    // HitRecord record;
    // if (!hitScene(ray, record))
    // {
    //     return color * dot;
    // }

    // if (t < record.t)
    // {
    //     return color * dot;
    // }

    // return Color::COLOR_BLACK;
    return Color::COLOR_BLACK;
}
