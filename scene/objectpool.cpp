#include "objectpool.h"
#include <limits>
#include <iostream>
#include "common.h"
#include <algorithm>
#include <cassert>

// #define _OBJECT_POOL_DEBUG_PRINT_

ObjectPool::ObjectPool()
{
    m_pHitter = new Hitter();
}

void ObjectPool::add(Geometry *pGeometry)
{
    m_objects.push_back(pGeometry);
}

void ObjectPool::add(Light *pLight)
{
    m_pLight = pLight;
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
    return m_pHitter->hitSceneWithLight(m_objects, m_pLight, ray, record, out_isLightHit);
}

bool ObjectPool::hitScene(const Ray &ray, HitRecord &record) const
{
    return m_pHitter->hitScene(m_objects, ray, record);
}

Color ObjectPool::getColorFromLight(const Ray &ray) const
{
    return m_pHitter->getColorFromLight(m_objects, m_pLight, ray);
}

std::vector<Geometry *> ObjectPool::getObjects() const
{
    return m_objects;
}
