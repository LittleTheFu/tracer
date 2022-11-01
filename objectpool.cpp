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

bool ObjectPool::hitSceneObject(const Ray &ray, float &tMin, int &outIndex, HitInfo &info)
{
    float t = std::numeric_limits<float>::max();
    tMin = t;
    bool hit = false;
    Vector3 p;

    int index = 0;
    outIndex = 0;

    for (std::vector<Ball>::iterator it = m_balls.begin(); it != m_balls.end(); it++)
    {
        index++;

        if (it->isInTheBall(ray.origin))
        {
            continue;
        }

        // use this
        Vector3 tempNormal;
        Vector3 tempReflect;
        if (ray.localHit(*it, t, p, tempNormal, tempReflect))
        // if (ray.hit(*it, t, p))
        {
            hit = true;

            if (t > 0 && t < tMin)
            {
                tMin = t;
                info.m_point = p;
                info.m_normal = tempNormal;
                // info.m_normal = it->getNormal(p);
                info.m_randomReflect = tempReflect;
                info.m_mtrl = it->mtrl;
                // std::cout << "****** :" << it->mtrl.specular << "*******" << std::endl;
                outIndex = index;
            }
        }
    }

    for (std::vector<Plane>::iterator it = m_planes.begin(); it != m_planes.end(); it++)
    {
        index++;

        if (it->isOnThePlane(ray.origin))
        {
            continue;
        }

        // if (ray.hit(*it, t, p))
        Vector3 normalTemp;
        Vector3 randomReflect;
        if (ray.localHit(*it, t, p, normalTemp, randomReflect))
        {
            hit = true;

            if (t > 0 && t < tMin)
            {
                tMin = t;
                info.m_point = p;
                info.m_normal = normalTemp;
                info.m_randomReflect = randomReflect;
                info.m_mtrl = it->mtrl;
                outIndex = index;
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
        return Color::COLOR_BLACK;
    }

    Color color = Color::COLOR_WHITE * dot;

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

bool ObjectPool::testLightReachable(const Ray &ray, const Vector3 &light)
{
    float t1 = std::numeric_limits<float>::max();

    int dummyIndex = 0;
    HitInfo dummyInfo;

    Ray lightRay = ray;
    // Vector3 dir = light - ray.origin;
    // dir.normalize();
    // lightRay.dir = dir;

    bool lastHit = hitSceneObject(lightRay, t1, dummyIndex, dummyInfo);

    if (!lastHit)
    {
        return true;
    }

    const float lightHitT = (light - lightRay.origin).length();

    if (lightHitT < t1)
    {
        return true;
    }

    return false;
}

Color ObjectPool::trace(const Ray &ray, int bounceNum, const HitRecord &currentState)
{
    if (bounceNum == 1)
    {
        // does this ray can hit the light?
        // return light * cos * cos * sample_f / pdf

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
    if(bounceNum == 2)
    {
        //trace to light
        Vector3 lightDir = m_pLight->getPosition() - record.point;
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

bool ObjectPool::traceWithTimes(const Ray &ray, int bounceNum, int &index, HitInfo &outInfo, const Material &currentMtrl)
{
    bounceNum -= 1;
    if (bounceNum <= 0)
    {
        // std::cout << "weight : " << w << std::endl;
        bool flag = testLightReachable(ray, m_light.getCenter());

        if (flag)
        {
            outInfo.m_mtrl = currentMtrl * Material::MTRL_WHITE;
            // outInfo.m_mtrl = Material::MTRL_WHITE;
        }
        else
        {
            outInfo.m_mtrl = currentMtrl * Material::MTRL_BLACK;
            // outInfo.m_mtrl = Material::MTRL_BLACK;
        }

        return flag;
    }

    float t = std::numeric_limits<float>::max();
    bool hit = false;

    HitInfo info;
    hit = hitSceneObject(ray, t, index, info);
    // outInfo = info;

    if (hit)
    {
        HitInfo newInfo;
        Vector3 n = info.m_normal;
        n.normalize();

        // Vector3 rayPos = info.m_point + n;
        Vector3 rayPos = info.m_point;

        // Vector3 rawDir = m_light.getCenter() - rayPos;
        // Vector3 rawDir = ray.dir.reflect(info.m_normal);
        Vector3 rawDir = info.m_randomReflect;
        Vector3 dir = rawDir;
        dir.normalize();

        Ray newRay = Ray(rayPos, dir);

        float thetaWeight = 1;
        if (bounceNum > 1)
        {
            thetaWeight = dir * n;

            if (thetaWeight < 0)
                thetaWeight = 0;
        }
        else
        {
            Vector3 lightDir = m_light.getCenter() - newRay.origin;
            lightDir.normalize();
            newRay.dir = lightDir;

            thetaWeight = lightDir * n;
            if (thetaWeight < 0)
                thetaWeight = 0;
        }

        // bool traceFlag = traceWithTimes(newRay, bounceNum, index, newInfo, w, info.m_mtrl);
        bool traceFlag = traceWithTimes(newRay, bounceNum, index, newInfo, info.m_mtrl);

        // const Material me_mtrl = currentMtrl * newInfo.m_mtrl * thetaWeight * Common::INV_PI;
        const Material me_mtrl = currentMtrl * newInfo.m_mtrl * thetaWeight * 2;
        const Material that_mtrl = newInfo.m_mtrl;

        outInfo.m_mtrl = me_mtrl;

        return traceFlag;
    }

    return false;
}