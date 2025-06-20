#include "objectpool.h"
#include <limits>
#include <iostream>
#include <algorithm>
#include <cassert>
#include "simpleHitter.h"
#include "bvh.h"
#include "config.h"

//-------------for refactory---------------------------
void ObjectPool::addPrimitive(std::shared_ptr<Primitive> primitive)
{
    primitives_.push_back(primitive);
}

void ObjectPool::addPrimitives(std::vector<std::shared_ptr<Primitive>> primitives)
{
    primitives_.insert(primitives_.end(), primitives.begin(), primitives.end());
}

void ObjectPool::addLight(std::shared_ptr<AreaLight> light)
{
    lights_.push_back(light);
}

const std::vector<std::shared_ptr<AreaLight>>& ObjectPool::getLights() const
{
    return lights_;
}
void ObjectPool::setVolume(std::shared_ptr<SphereVolume> volume)
{
    volume_ = volume;
}
//-----------------end------------------------------

bool ObjectPool::isVolumePrimitive(std::shared_ptr<const Primitive> primitive) const
{
    if(volume_ == nullptr)
        return false;

    return (volume_->getGeometry() == primitive->getGeometry());
}

ObjectPool::ObjectPool(bool useBVH) : lights_({})
{
    if (useBVH)
        m_pHitter = new BVH();
    else
        m_pHitter = new SimperHitter();
}

void ObjectPool::initHitter()
{
    m_pHitter->init(lights_, primitives_);
}

void ObjectPool::log()
{
    size_t num = primitives_.size();
    std::cout << "pool size : " << num << std::endl;
}

// void ObjectPool::add(std::vector<std::shared_ptr<Geometry>> objects)
// {
//     for(auto it = objects.begin(); it != objects.end(); it++)
//     {
//         m_objects.push_back(*it);
//     }
// }

// void ObjectPool::add(std::shared_ptr<Geometry> pGeometry)
// {
//     m_objects.push_back(pGeometry);
// }

// void ObjectPool::add(std::shared_ptr<Light> pLight)
// {
//     m_pLight = pLight;
// }

void ObjectPool::applyTransfrom(Transform t)
{
    for (auto it = primitives_.begin(); it != primitives_.end(); it++)
    {
        (*it)->getGeometry()->applyTransform(t);
    }

    // if(light_)
    //     light_->applyTransform(t);
}

void ObjectPool::buildBoundBox()
{
    for (auto it = primitives_.begin(); it != primitives_.end(); it++)
    {
        (*it)->getGeometry()->buildBoundBox();
    }
}

bool ObjectPool::hitScene(const Ray &ray, Interaction &interaction) const
{
    bool isHit = m_pHitter->hitGeometryObjectOnly(ray, interaction);
    
    if(isHit)
    {
        if(isVolumePrimitive(interaction.primitive))
        {
            interaction.is_volume_boundary_hit = true;
            interaction.is_surface_hit = false;
        }
        else
        {
            interaction.is_volume_boundary_hit = false;
            interaction.is_surface_hit = true;
        }
    }
    else
    {
        interaction.is_volume_boundary_hit = false;
        interaction.is_surface_hit = false;
    }


    return isHit;
}

Color ObjectPool::getColorFromLight(const Ray &ray, int index) const
{
    return m_pHitter->getColorFromLight(ray, index);
}

std::vector<std::shared_ptr<Primitive>> ObjectPool::getPrimitives() const
{
    return primitives_;
}

// bool ObjectPool::validBVH() const
// {
//     BVH *bvh = dynamic_cast<BVH*>(m_pHitter);
//     if(!bvh)
//         return false;
        
//     bool allFound = true;

//     for(auto it = m_objects.begin(); it != m_objects.end(); it++)
//     {
//         if(bvh->search(*it))
//         {
//             std::cout << "found" <<std::endl;
//         }
//         else
//         {
//             allFound = false;
//             std::cout << "not found" <<std::endl;
//         }
//     }

//     std::cout << "VALID ALL FOUND: " << allFound << "   &&&&&" << std::endl;

//     return allFound;
// }