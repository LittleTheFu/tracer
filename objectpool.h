#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <vector>
#include "ball.h"
#include "plane.h"
#include "ray.h"

class ObjectPool
{
public:
    void add(const Ball &ball);
    void add(const Plane &plane);
    bool hit(const Ray &ray, bool &isBall, int &outIndex, Vector3 &hitPoint, Vector3 &hitNormal);

    void trace(const Ray &ray);

private:
    std::vector<Ball> m_balls;
    std::vector<Plane> m_planes;
};

#endif