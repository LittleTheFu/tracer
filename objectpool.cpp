#include "objectpool.h"
#include <limits>
#include <iostream>
#include "common/common.h"
#include <algorithm>
#include <cassert>

// #define _OBJECT_POOL_DEBUG_PRINT_

ObjectPool::ObjectPool()
{
}

void ObjectPool::add(Geometry *pGeometry)
{
    m_objects.push_back(pGeometry);
}

void ObjectPool::add(Light *pLight)
{
    m_pLight = pLight;
}

void ObjectPool::add(Mist *pMist)
{
    m_pMist = pMist;
}

void ObjectPool::applyTransfrom(Transform t)
{
    for (std::vector<Geometry *>::iterator it = m_objects.begin(); it != m_objects.end(); it++)
    {
        (*it)->applyTransform(t);
    }

    m_pLight->applyTransform(t);
}

bool ObjectPool::hitScene(const Ray &ray, HitRecord &record, bool mist = false) const
{
    bool hit = false;
    float tMin = Common::FLOAT_MAX;

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

    if(mist)
    {
        HitRecord mistRecord;
        bool bHitMist = m_pMist->hit(ray, mistRecord);

        record.t0 = mistRecord.t0;
        record.t1 = mistRecord.t1;
        record.isMistHit = bHitMist;
    }

    return hit;
}

Color ObjectPool::getColorFromLight(const Ray &ray) const
{
    float t;
    Vector3 normal;
    float dot;
    if (!m_pLight->hit(ray, t, normal, dot))
    {
        // m_pLight->hit(ray, t, normal, dot);
        return Color::COLOR_BLACK;
    }

    Color color = Color::COLOR_WHITE;

    HitRecord record;
    if (!hitScene(ray, record))
    {
        return color * dot;
    }

    if (t < record.t)
    {
        return color * dot;
    }

    return Color::COLOR_BLACK;
}

Color ObjectPool::trace(const Ray &ray, int bounceNum, const HitRecord &currentState) const
{
    if (bounceNum == 1)
    {
        // does this ray can hit the light?
        // return light * cos * cos * sample_f / pdf
        if (currentState.isMirror)
        {
            return Color::COLOR_BLACK;
        }

        Color lightColor = getColorFromLight(ray);
        float ttt = 1 / currentState.reflectPdf;
        Color retColor = lightColor * currentState.dot * currentState.f / currentState.reflectPdf;

        return retColor;
    }

    HitRecord record;
    if (!hitScene(ray, record))
    {
        return Color::COLOR_BLACK;
    }

    Ray newRay(record.point, record.reflect);
    if (bounceNum == 2 && !record.isMirror)
    {
        Vector3 lightSurfacePoint = m_pLight->sample(record.point, record.reflectPdf);
        Vector3 lightDir = lightSurfacePoint - record.point;
        lightDir.normalize();

        record.reflect = lightDir;
        record.dot = record.normal * lightDir; // dot less than 0

        newRay.dir = lightDir;
    }
    if (record.isMirror && bounceNum > 3)
    {
        // std::cout << "mirror" << std::endl;
    }
    Color inputColor = trace(newRay, bounceNum - 1, record);

    assert(currentState.reflectPdf > 0);
    Color ccolor = currentState.f * inputColor * currentState.dot / currentState.reflectPdf;

    // if (ccolor != color)
    // {
    //     std::cout << "color not equal" << std::endl;
    // }
    return ccolor;
}