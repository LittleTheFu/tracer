#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <vector>
#include "ball.h"
#include "plane.h"
#include "ray.h"
#include "hitinfo.h"

class ObjectPool
{
public:
    ObjectPool();

    void setLight(float x, float y, float z, float r);

    void add(const Ball &ball);
    void add(const Plane &plane);
    bool hit(const Ray &ray, bool &isBall, int &outIndex, Vector3 &hitPoint, Vector3 &hitNormal);

    void trace(const Ray &ray);
    bool startTrace(const Ray &ray, int &index, int maxDepth, float &outFactor);
    bool lightTrace(const Ray &ray, int &index, int depth, int maxDepth, float inFactor, float &outFactor);
    bool directTrace(const Ray &ray, int &index, HitInfo &outInfo);
    bool traceWithTimes(const Ray &ray, int bounceNum, int &index, HitInfo &outInfo, float &w, const Material &currentMtrl);
    bool testLightReachable(const Ray &ray, const Vector3 &light);

    bool hitSceneObjectOld(const Ray &ray, float &tMin, int &outIndex, HitInfo &info);
    bool hitSceneObject(const Ray &ray, float &tMin, int &outIndex, HitInfo &info);

private:
    std::vector<Ball> m_balls;
    std::vector<Plane> m_planes;

    Ball m_light;

    float m_attenuation;
};

#endif