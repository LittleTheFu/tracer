#include "objectpool.h"

void ObjectPool::add(const Ball &ball)
{
    m_balls.push_back(ball);
}

bool ObjectPool::hit(const Ray &ray)
{
    std::vector<Ball>::iterator it; // declare an iterator to a vector of strings

    for (it = m_balls.begin(); it != m_balls.end(); it++)
    {
        if (ray.hit(*it))
            return true;
    }

    return false;
}