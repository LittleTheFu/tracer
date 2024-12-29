#include "objectpool.h"
#include <limits>
#include <iostream>
#include <algorithm>
#include <cassert>
#include "simpleHitter.h"
#include "bvh.h"
#include "config.h"

ObjectPool::ObjectPool() : m_pLight(nullptr)
{
    if (configUseBVH)
        m_pHitter = new BVH();
    else
        m_pHitter = new SimperHitter();
}

void ObjectPool::initHitter()
{
    m_pHitter->init(m_objects, m_pLight);
}

void ObjectPool::log()
{
    size_t num = m_objects.size();
    std::cout << "pool size : " << num << std::endl;
}

void ObjectPool::add(std::vector<std::shared_ptr<Geometry>> objects)
{
    for(auto it = objects.begin(); it != objects.end(); it++)
    {
        m_objects.push_back(*it);
    }
}

void ObjectPool::add(std::shared_ptr<Geometry> pGeometry)
{
    m_objects.push_back(pGeometry);
}

void ObjectPool::add(std::shared_ptr<Light> pLight)
{
    m_pLight = pLight;
}

void ObjectPool::applyTransfrom(Transform t)
{
    for (auto it = m_objects.begin(); it != m_objects.end(); it++)
    {
        (*it)->applyTransform(t);
    }

    if(m_pLight)
        m_pLight->applyTransform(t);
}

void ObjectPool::buildBoundBox()
{
    for (auto it = m_objects.begin(); it != m_objects.end(); it++)
    {
        (*it)->buildBoundBox();
        // std::cout << (*it)->getClassName() << std::endl;
        // std::cout << (*it)->getBoundBox() << std::endl;
    }
}

bool ObjectPool::hitScene(const Ray &ray, HitRecord &record) const
{
    return m_pHitter->hitGeometryObjectOnly(ray, record);
}

Color ObjectPool::getColorFromLight(const Ray &ray) const
{
    return m_pHitter->getColorFromLight(ray);
}

std::vector<std::shared_ptr<Geometry>> ObjectPool::getObjects() const
{
    return m_objects;
}

bool ObjectPool::validBVH() const
{
    BVH *bvh = dynamic_cast<BVH*>(m_pHitter);
    if(!bvh)
        return false;
        
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

    return allFound;
}