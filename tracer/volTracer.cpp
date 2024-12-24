// Copyright 2024 <fu>
#include "volTracer.h"
#include "mathUtility.h"
#include <memory>

Color VolTracer::trace(std::shared_ptr<const ObjectPool> pool,
                        Ray &ray, int bounceNum,
                        const HitRecord &currentState) const {
    HitRecord record;
    bool isHit = pool->hitScene(ray, record);
    float tMax = record.t;

    float t;
    if (ray.media.sigma_major == 0.0f)
        t = tMax;
    else
        t = MathUtility::sampleExponential(ray.media.sigma_major);

    while (t < tMax) {
        float sigma_a = ray.media.sigma_a;
        float sigma_s = ray.media.sigma_s;
        float sigma_n = ray.media.sigma_n;

        Vector3 pt = ray.getPosition(t);
        Vector3 org(50, 0, 320);
        float lenSqr = (pt - org).lenthSqr();

        Vector3 fake_pt(pt * 1);

        int x = static_cast<int>(fake_pt.x);
        int y = static_cast<int>(fake_pt.y);
        int z = static_cast<int>(fake_pt.z);
        sigma_a = m_vox.get(x, y, z);
        if (sigma_a > 0) {
            sigma_a *= 10;
            int pss = 23;
        }
        if (sigma_a < 0)
            sigma_a = 0;

        int index = MathUtility::sampleFromWeights({sigma_a, sigma_s, sigma_n});

        if (index == 0) {
            return ray.media.emitColor;
        } else if (index == 1) {
            bounceNum--;
            if (bounceNum == 1)
                return Color::COLOR_RED;

            // scattering
            Vector3 dir = Vector3::sampleUniformFromSphere();
            Ray newRay(ray.getPosition(t), dir);
            return trace(pool, newRay, bounceNum, record);
        } else {
            t += 50 * MathUtility::sampleExponential(ray.media.sigma_major);
            // t += 20;
        }
    }

    if (isHit) {
        Ray new_ray(ray.getPosition(tMax) + ray.dir * 0.01f, ray.dir);
        new_ray.media = record.getMeida(ray.dir);

        return trace(pool, new_ray, bounceNum, record);
    }

    return Color::COLOR_BLACK;
}

Color VolTracer::traceFirstBounce(std::shared_ptr<const ObjectPool> pool, Ray &ray) const {
    return Color::COLOR_BLACK;
}
