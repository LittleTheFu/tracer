#include "objectpool.h"
#include <limits>
#include <iostream>
#include "common.h"
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

void ObjectPool::buildBoundBox()
{
    for (std::vector<Geometry *>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
    {
        (*it)->buildBoundBox();
        std::cout << (*it)->getClassName() << std::endl;
        std::cout << (*it)->getBoundBox() << std::endl;
    }
}

bool ObjectPool::hitSceneWithLight(const Ray &ray, HitRecord &record, bool &out_isLightHit) const
{
    out_isLightHit = false;

    bool hit = false;
    float tMin = Common::FLOAT_MAX;

    for (std::vector<Geometry *>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
    {
        HitRecord tempRecord;

        if ((*it)->hit(ray, tempRecord, nullptr))
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
    bool isLightHit = m_pLight->hit(ray, t, normal, dotLight);
    if( t < tMin)
    {
        out_isLightHit = true;
        hit = true;

        record.dotLight = dotLight;
    }

    return hit;
}

bool ObjectPool::hitScene(const Ray &ray, HitRecord &record, bool mist, Light *pLight) const
{
    bool hit = false;
    float tMin = Common::FLOAT_MAX;

    for (std::vector<Geometry *>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
    {
        HitRecord tempRecord;

        if ((*it)->hit(ray, tempRecord, pLight))
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

std::vector<Geometry *> ObjectPool::getObjects() const
{
    return m_objects;
}
