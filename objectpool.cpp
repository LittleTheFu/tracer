#include "objectpool.h"
#include <limits>
#include <iostream>

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
                hitNormal = it->getNormal(hitPoint);
                outIndex = index;
            }
        }
    }

    for (std::vector<Plane>::iterator it = m_planes.begin(); it != m_planes.end(); it++)
    {
        index++;

        if (ray.hit(*it, t, p))
        {
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

    return hit;
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