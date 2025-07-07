#include "sphereVolume.h"

SphereVolume::SphereVolume(std::shared_ptr<Medium> medium, const Vector3 &center, float radius)
    : Volume(medium), center_(center), radius_(radius)
{
    ball_ = std::make_shared<Ball>(Vector3::ZERO, center_, radius_);
}

bool SphereVolume::intersect(const Ray &ray, float &t0, float &t1) const
{
    return ball_->hit(ray, t0, t1);
}

std::shared_ptr<Ball> SphereVolume::getGeometry() const
{
    return ball_;
}