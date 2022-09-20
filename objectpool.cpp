#include "objectpool.h"

void ObjectPool::add(const Ball &ball)
{
    m_balls.push_back(ball);
}

void ObjectPool::add(const Plane &plane)
{
    m_planes.push_back(plane);
}

bool ObjectPool::hit(const Ray &ray)
{
    for (std::vector<Ball>::iterator it = m_balls.begin(); it != m_balls.end(); it++)
    {
        if (ray.hit(*it))
            return true;
    }

    for (std::vector<Plane>::iterator it = m_planes.begin(); it != m_planes.end(); it++)
    {
        if (ray.hit(*it))
            return true;
    }

    return false;
}