#ifndef _SPHERE_VOLUME_H_
#define _SPHERE_VOLUME_H_

#include "volume.h"
#include "vector.h"
#include "ball.h"

class SphereVolume : public Volume
{
public:
    SphereVolume(std::shared_ptr<const Medium> medium, const Vector3& center, float radius);

    bool intersect(const Ray& ray, float& t0, float& t1) const override;
    std::shared_ptr<Ball> getGeometry() const;

private:
    Vector3 center_;
    float radius_;

    std::shared_ptr<Ball> ball_;
};

#endif