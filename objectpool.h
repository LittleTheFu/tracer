#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <vector>
#include "ball.h"
#include "ray.h"

class ObjectPool
{
public:
    void add(const Ball &ball);
    bool hit(const Ray &ray);

private:
    std::vector<Ball> m_balls;
};

#endif