#include "objectpool.h"
#include <limits>
#include <iostream>
#include "hitinfo.h"
#include "common.h"
#include <algorithm>
#include <cassert>

// #define _OBJECT_POOL_DEBUG_PRINT_

ObjectPool::ObjectPool()
{
    m_attenuation = 0.99999999f;
    // m_attenuation = 1;
}

void ObjectPool::setLight(float x, float y, float z, float r)
{
    m_light.setPos(x, y, z);
    m_light.setR(r);
}

void ObjectPool::add(const Ball &ball)
{
    m_balls.push_back(ball);
}

void ObjectPool::add(const Plane &plane)
{
    m_planes.push_back(plane);
}

void ObjectPool::add(const Geometry *pGeometry)
{
    m_objects.push_back(pGeometry);
}

void ObjectPool::add(const Light *pLight)
{
    m_pLight = pLight;
}

bool ObjectPool::hitScene(const Ray &ray, HitRecord &record)
{
    bool hit = false;
    float tMin = Common::FLOAT_MAX;

    for (std::vector<const Geometry *>::iterator it = m_objects.begin(); it != m_objects.end(); it++)
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

Color ObjectPool::getColorFromLight(const Ray &ray)
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

bool ObjectPool::isLightReachable(const Ray &ray, const Vector3 &light)
{
    HitRecord record;

    if (!hitScene(ray, record))
    {
        return true;
    }

    const float lightHitT = (light - ray.origin).length();

    return (lightHitT < record.t);
}

Color ObjectPool::trace(const Ray &ray, int bounceNum, const HitRecord &currentState)
{
    if (bounceNum == 1)
    {
        // does this ray can hit the light?
        // return light * cos * cos * sample_f / pdf
        if(currentState.isMirror)
        {
            return Color::COLOR_BLACK;
        }

        Color lightColor = getColorFromLight(ray);
        float ttt = 1 / currentState.reflectPdf;
        Color rretColor = lightColor * currentState.dot * currentState.f / currentState.reflectPdf;

        // Color retColor = lightColor * currentState.dot * currentState.f * 2 * Common::PI;

        // if (rretColor != retColor)
        // {
        //     std::cout << "light color is not equal" << std::endl;
        // }

        return rretColor;
    }

    HitRecord record;
    if (!hitScene(ray, record))
    {
        return Color::COLOR_BLACK;
    }

    Ray newRay(record.point, record.reflect);
    if (bounceNum == 2 && !currentState.isMirror)
    {
        Vector3 lightSurfacePoint = m_pLight->sample(record.point, record.reflectPdf);
        Vector3 lightDir = lightSurfacePoint - record.point;
        lightDir.normalize();

        record.reflect = lightDir;
        record.dot = record.normal * lightDir;

        newRay.dir = lightDir;
    }
    Color inputColor = trace(newRay, bounceNum - 1, record);

    assert(currentState.reflectPdf > 0);
    Color ccolor = currentState.f * inputColor * currentState.dot / currentState.reflectPdf;
    // Color color = inputColor * currentState.f * currentState.dot * 2 * Common::PI;

    // if (ccolor != color)
    // {
    //     std::cout << "color not equal" << std::endl;
    // }
    return ccolor;
}