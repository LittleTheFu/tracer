#include "objectpool.h"
#include <limits>
#include <iostream>
#include "common.h"
#include <algorithm>
#include <cassert>
#include "hitter.h"
#include "bvh.h"

// #define _OBJECT_POOL_DEBUG_PRINT_

ObjectPool::ObjectPool()
{
    // m_pHitter = new Hitter();
    m_pHitter = new BVH();
}

void ObjectPool::initHitter()
{
    m_pHitter->init(m_objects, m_pLight);
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
        // std::cout << (*it)->getClassName() << std::endl;
        // std::cout << (*it)->getBoundBox() << std::endl;
    }
}

bool ObjectPool::hitSceneWithLight(const Ray &ray, HitRecord &record, bool &out_isLightHit) const
{
    return m_pHitter->hitSceneWithLight(ray, record, out_isLightHit);
}

bool ObjectPool::hitScene(const Ray &ray, HitRecord &record) const
{
    return m_pHitter->hitGeometryObjectOnly(ray, record);
}

Color ObjectPool::getColorFromLight(const Ray &ray) const
{
    return m_pHitter->getColorFromLight(ray);
}

std::vector<Geometry *> ObjectPool::getObjects() const
{
    return m_objects;
}

bool ObjectPool::validBVH() const
{
    BVH *bvh = (BVH*)m_pHitter;
    bool allFound = true;

    for(auto it = m_objects.begin(); it != m_objects.end(); it++)
    {
        if(bvh->search(*it))
        {
            std::cout << "found" <<std::endl;
        }
        else
        {
            allFound = false;
            std::cout << "not found" <<std::endl;
        }
    }

    std::cout << "VALID ALL FOUND: " << allFound << "   &&&&&" << std::endl;

    return true;
}