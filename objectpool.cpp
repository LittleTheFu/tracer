#include "objectpool.h"
#include <limits>

void ObjectPool::add(const Ball &ball)
{
    m_balls.push_back(ball);
}

void ObjectPool::add(const Plane &plane)
{
    m_planes.push_back(plane);
}

bool ObjectPool::hit(const Ray &ray, bool &isBall)
{
    float t = std::numeric_limits<float>::max();
    float tMin = t;
    bool hit = false;
    Vector3 p;

    for (std::vector<Ball>::iterator it = m_balls.begin(); it != m_balls.end(); it++)
    {
        if (ray.hit(*it, t, p))
        {
            hit = true;

            if (t >= 0 && t < tMin)
            {
                isBall = true;
                tMin = t;
            }
        }
    }

    for (std::vector<Plane>::iterator it = m_planes.begin(); it != m_planes.end(); it++)
    {
        if (ray.hit(*it, t, p))
        {
            hit = true;

            if (t >= 0 && t < tMin)
            {
                tMin = t;
                isBall = false;
            }
        }
    }

    return hit;
}