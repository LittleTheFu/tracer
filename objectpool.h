#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <vector>
#include "ball.h"
#include "plane.h"
#include "ray.h"
#include "hitinfo.h"
#include "geometry.h"
#include "hitrecord.h"
#include "color.h"
#include "light.h"

class ObjectPool
{
public:
    ObjectPool();

    void setLight(float x, float y, float z, float r);

    void add(const Ball &ball);
    void add(const Plane &plane);
    void add(const Geometry *pGeometry);
    void add(const Light *pLight);

    bool traceWithTimes(const Ray &ray, int bounceNum, int &index, HitInfo &outInfo, const Material &currentMtrl);
    bool testLightReachable(const Ray &ray, const Vector3 &light);
    bool hitSceneObject(const Ray &ray, float &tMin, int &outIndex, HitInfo &info);
    bool hitScene(const Ray &ray, HitRecord &record);

    Color trace(const Ray &ray, int bounceNum, const HitRecord &currentState);
    bool isLightReachable(const Ray &ray, const Vector3 &light);
    Color getColorFromLight(const Ray &ray);

private:
    std::vector<Ball> m_balls;
    std::vector<Plane> m_planes;
    std::vector<const Geometry *> m_objects;

    const Light *m_pLight;

    Ball m_light;

    float m_attenuation;
};

#endif