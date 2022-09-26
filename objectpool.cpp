#include "objectpool.h"
#include <limits>
#include <iostream>
#include "hitinfo.h"

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

bool ObjectPool::hit(const Ray &ray, bool &isBall, int &outIndex, Vector3 &hitPoint, Vector3 &hitNormal)
{
    float t = std::numeric_limits<float>::max();
    float tMin = t;
    bool hit = false;
    Vector3 p;

    int index = 0;
    outIndex = 0;

    for (std::vector<Ball>::iterator it = m_balls.begin(); it != m_balls.end(); it++)
    {
        index++;

        if (ray.hit(*it, t, p))
        {
            hit = true;

            if (t >= 0 && t < tMin)
            {
                isBall = true;
                tMin = t;
                hitPoint = p;
                hitNormal = it->getNormal(p);
                outIndex = index;
            }
        }
    }

    // std::cout << "------BEGIN------" << std::endl;
    for (std::vector<Plane>::iterator it = m_planes.begin(); it != m_planes.end(); it++)
    {
        index++;

        if (ray.hit(*it, t, p))
        {
            // std::cout << "HIT : " << index << " " << t << std::endl;
            hit = true;

            if (t >= 0 && t < tMin)
            {
                tMin = t;
                isBall = false;
                hitPoint = p;
                hitNormal = it->normal;
                outIndex = index;
            }
        }
    }
    // std::cout << "------END------" << std::endl;

    index = 100;
    if (ray.hit(m_light, t, p))
    {
        // std::cout << "HIT : " << index << " " << t << std::endl;
        hit = true;

        if (t >= 0 && t < tMin)
        {
            tMin = t;
            isBall = false;
            hitPoint = p;
            hitNormal = m_light.getNormal(p);
            outIndex = index;
        }
    }

    return hit;
}

bool ObjectPool::startTrace(const Ray &ray, int &index, int maxDepth, float &outFactor)
{
    return lightTrace(ray, index, 0, maxDepth, 1.0f, outFactor);
}

bool ObjectPool::lightTrace(const Ray &ray, int &index, int depth, int maxDepth, float inFactor, float &outFactor)
{
    if (depth > maxDepth)
    {
        // std::cout << "miss!" << std::endl;
        outFactor = inFactor;
        return false;
    }

    bool isBall = false;
    bool isHit = false;

    Vector3 point;
    Vector3 normal;

    int outIndex;
    isHit = hit(ray, isBall, outIndex, point, normal);
    index = outIndex;

    if (ray.dir.isInSameSide(normal))
    {
        outFactor = inFactor;
        return false;
    }

    if (outIndex == 100)
    {
        // std::cout << "depth : " << depth << std::endl;
        outFactor = inFactor;
        return true;
    }

    const Vector3 dir = ray.dir.reflect(normal);
    Vector3 offset = ray.dir;
    offset.normalize();

    Vector3 n = normal;
    n.normalize();
    const Ray newRay = Ray(point + n, dir);

    int dummpIndex = 0;
    if (isHit)
    {
        return lightTrace(newRay, dummpIndex, depth + 1, maxDepth, inFactor * m_attenuation, outFactor);
    }

    return false;
}

void ObjectPool::trace(const Ray &ray)
{
    std::cout << "---------------------" << std::endl;
    std::cout << "START POS : (" << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << ")" << std::endl;
    std::cout << "START dir : (" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ")" << std::endl;

    bool isBall = false;
    bool isHit = false;

    Vector3 point;
    Vector3 normal;

    int outIndex;
    isHit = hit(ray, isBall, outIndex, point, normal);

    if (ray.dir.isInSameSide(normal))
    {
        std::cout << "**********" << std::endl;
        std::cout << "SAME SIDE !!!" << std::endl;
        std::cout << "OLD_DIR : (" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ")" << std::endl;
        std::cout << "HIT_POS : (" << point.x << "," << point.y << "," << point.z << ")" << std::endl;
        std::cout << "HIT_NORMAL : (" << normal.x << "," << normal.y << "," << normal.z << ")" << std::endl;

        std::cout << "IS_BALL : " << isBall << std::endl;
        std::cout << "**********" << std::endl;
        return;
    }

    const Vector3 dir = ray.dir.reflect(normal);
    // const Ray newRay = Ray(point + dir, dir);
    Vector3 offset = ray.dir;
    offset.normalize();

    Vector3 n = normal;
    n.normalize();
    const Ray newRay = Ray(point + n, dir);

    if (isHit)
    {
        // std::cout << "OLD_DIR : (" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ")" << std::endl;
        std::cout << "HIT_POS : (" << point.x << "," << point.y << "," << point.z << ")" << std::endl;
        std::cout << "HIT_NORMAL : (" << normal.x << "," << normal.y << "," << normal.z << ")" << std::endl;
        std::cout << "NEW_DIR : (" << dir.x << "," << dir.y << "," << dir.z << ")" << std::endl;

        trace(newRay);
    }

    std::cout << "NORMAL END!!!!" << std::endl;
    std::cout << "OLD_DIR : (" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ")" << std::endl;
    std::cout << "NEW_DIR : (" << dir.x << "," << dir.y << "," << dir.z << ")" << std::endl;
    std::cout << "NORMAL : (" << normal.x << "," << normal.y << "," << normal.z << ")" << std::endl;
}

bool ObjectPool::hitSceneObjectOld(const Ray &ray, float &tMin, int &outIndex, HitInfo &info)
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
        if (ray.hit(*it, t, p))
        {
            hit = true;

            if (t > 0 && t < tMin)
            {
                tMin = t;
                info.m_point = p;
                info.m_normal = it->getNormal(p);
                info.m_mtrl = it->mtrl;
                outIndex = index;
            }
        }
    }

    for (std::vector<Plane>::iterator it = m_planes.begin(); it != m_planes.end(); it++)
    {
        index++;

        if (it->isInSamePlane(ray.origin))
        {
            continue;
        }

        if (ray.hit(*it, t, p))
        {
            hit = true;

            if (t > 0 && t < tMin)
            {
                tMin = t;
                info.m_point = p;
                info.m_normal = it->normal;
                info.m_mtrl = it->mtrl;
                outIndex = index;
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
        if (ray.localHit(*it, t, p, tempNormal))
        // if (ray.hit(*it, t, p))
        {
            hit = true;

            if (t > 0 && t < tMin)
            {
                tMin = t;
                info.m_point = p;
                info.m_normal = tempNormal;
                // info.m_normal = it->getNormal(p);
                info.m_mtrl = it->mtrl;
                outIndex = index;
            }
        }
    }

    for (std::vector<Plane>::iterator it = m_planes.begin(); it != m_planes.end(); it++)
    {
        index++;

        if (it->isInSamePlane(ray.origin))
        {
            continue;
        }

        // if (ray.hit(*it, t, p))
        Vector3 normalTemp;
        if (ray.localHit(*it, t, p, normalTemp))
        {
            hit = true;

            if (t > 0 && t < tMin)
            {
                tMin = t;
                info.m_point = p;
                info.m_normal = normalTemp;
                info.m_mtrl = it->mtrl;
                outIndex = index;
            }
        }
    }

    return hit;
}

bool ObjectPool::testLightReachable(const Ray &ray, const Vector3 &light)
{
    float t1 = std::numeric_limits<float>::max();

    int dummyIndex = 0;
    HitInfo dummyInfo;

    bool lastHit = hitSceneObject(ray, t1, dummyIndex, dummyInfo);

    if (!lastHit)
    {
        return true;
    }

    const float lightHitT = (light - ray.origin).length();

    if (lightHitT < t1)
    {
        return true;
    }

    return false;
}

bool ObjectPool::traceWithTimes(const Ray &ray, int bounceNum, int &index, HitInfo &outInfo)
{

    bounceNum -= 1;
    if (bounceNum <= 0)
    {
        return testLightReachable(ray, m_light.getCenter());
    }

    float t = std::numeric_limits<float>::max();
    bool hit = false;

    HitInfo info;
    hit = hitSceneObject(ray, t, index, info);
    outInfo = info;

    if (hit)
    {
        HitInfo newInfo;
        Vector3 offset = info.m_normal;
        offset.normalize();

        Vector3 rayPos = info.m_point + offset;

        Vector3 rawDir = m_light.getCenter() - rayPos;
        Vector3 dir = rawDir;
        dir.normalize();

        const Ray newRay = Ray(rayPos, dir);

        return traceWithTimes(newRay, bounceNum, index, newInfo);
    }

    return false;

    // float t = std::numeric_limits<float>::max();
    // bool hit = false;

    // HitInfo info;
    // hit = hitSceneObject(ray, t, index, info);
    // outInfo = info;

    // if (hit)
    // {
    //     Vector3 offset = info.m_normal;
    //     offset.normalize();
    //     Vector3 rayPos = info.m_point + offset;

    //     // return testLightReachable(rayPos, m_light.getCenter());
    //     return true;
    // }

    // return false;
}

bool ObjectPool::directTrace(const Ray &ray, int &index, HitInfo &outInfo)
{
#ifdef _OBJECT_POOL_DEBUG_PRINT_
    std::cout << "!!!!!!!!!!" << std::endl;

    std::cout << "ray_pos: (" << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << ")" << std::endl;
    std::cout << "ray_dir: (" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ")" << std::endl;
#endif

    float t = std::numeric_limits<float>::max();
    bool hit = false;

    HitInfo info;
    hit = hitSceneObject(ray, t, index, info);
    outInfo = info;

    if (hit)
    {
        Vector3 offset = info.m_normal;
        offset.normalize();
        Vector3 rayPos = info.m_point + offset;
        Vector3 rawDir = m_light.getCenter() - rayPos;
        Vector3 dir = rawDir;
        dir.normalize();

        const Ray newRay = Ray(rayPos, dir);

        return testLightReachable(newRay, m_light.getCenter());
    }

    return false;
}

// #ifdef _OBJECT_POOL_DEBUG_PRINT_
//     std::cout << "hit_pos: (" << point.x << "," << point.y << "," << point.z << ")" << std::endl;
//     std::cout << "hit_normal: (" << normal.x << "," << normal.y << "," << normal.z << ")" << std::endl;
//     std::cout << "new_ray_pos: (" << newRay.origin.x << "," << newRay.origin.y << "," << newRay.origin.z << ")" << std::endl;
//     std::cout << "new_raw_dir: (" << rawDir.x << "," << rawDir.y << "," << rawDir.z << ")" << std::endl;
//     std::cout << "new_ray_dir: (" << newRay.dir.x << "," << newRay.dir.y << "," << newRay.dir.z << ")" << std::endl;
//     std::cout << "second_hit_index : " << dummyIndex << std::endl;
//     std::cout << "second_hit_point:(" << dummyPoint.x << "," << dummyPoint.y << "," << dummyPoint.z << ")" << std::endl;
//     std::cout << "second_hit_normal:(" << dummyNormal.x << "," << dummyNormal.y << "," << dummyNormal.z << ")" << std::endl;
// #endif

// #ifdef _OBJECT_POOL_DEBUG_PRINT_
//     std::cout << "light_pos : ( " << lightCenter.x << "," << lightCenter.y << "," << lightCenter.z << ")" << std::endl;
//     std::cout << "object_t : " << t1 << std::endl;
//     std::cout << "light_t : " << lightHitT << std::endl;
// #endif